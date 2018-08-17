#include "city_view.h"
#include "painter.h"
#include "city.h"
#include "road_view.h"
#include "sizes.h"

#include <iostream>
#include <algorithm>
#include <sstream>

CityView::CityView(Game* game, City* city) : NodeView(game, city), selected_road_(0) {}


RoadView* CityView::GetSelectedRoad()
{
	return selected_road_;
}

void CityView::Draw(Painter* painter) const {
	City* city = (City*) node_;
	Color city_color = city->GetOwner() == 0 ? NEUTRAL_CITY_COLOR : CITY_COLORS[city->GetOwner()->GetId()];
	Circle city_image;
	if (!selected_by_.empty()) {
		Color outline_color = {0, 0, 0};
		for (int id : selected_by_) {
			outline_color.r += SELECTION_COLORS[id].r;
			outline_color.g += SELECTION_COLORS[id].g;
			outline_color.b += SELECTION_COLORS[id].b;

	    	std::stringstream ss;
	    	ss << city->GetSyla() << std::endl << city->GetWall();
			Text text = {id == 0 ? -1 : 0.55, -1, ss.str()};     	
			painter->Draw(text);
		}
		outline_color.r /= selected_by_.size();
		outline_color.g /= selected_by_.size();
		outline_color.b /= selected_by_.size();
		city_image = {city->x(), city->y(), CITY_RADIUS, city_color, CITY_RADIUS / 5, outline_color};
	}
	else {
		city_image = {city->x(), city->y(), CITY_RADIUS, city_color};
	}
    painter->Draw(city_image);
}

void CityView::RoadSelect() {
	City* city = (City*) node_;
	if (selected_road_ != 0) {
		selected_road_->DeselectFromCity(city->GetIndex());
		selected_road_ = 0;
	}
	else {
		const std::vector<Road*> roads = city->GetRoads();
		if (roads.empty()) {
			return;
		}
		selected_road_ = (RoadView*) roads[0]->GetView(game_);
		selected_road_->SelectFromCity(city->GetIndex());
	}
}

NodeView* CityView::NextVertically(int direction) {
	if (selected_road_ == 0) {
		return NodeView::NextVertically(direction);
	}
	else {
		return NextHorizontally(direction);
	}
}

NodeView* CityView::NextHorizontally(int direction) {
	if (selected_road_ == 0) {
		return NodeView::NextHorizontally(direction);
	}
	else {
		City* city = (City*) node_;
		const std::vector<Road*> roads = city->GetRoads();
		Road* target = 0;
		for (auto road: roads) {
			if (road == selected_road_->GetRoad()) {
				continue;
			}
			//bool order = AreInOrder(selected_road_->GetRoad(), road, target);
			// if (direction < 0) {
			// 	order = !order;
			// }

			if (target == 0 || 
				(direction > 0 && AreInOrder(selected_road_->GetRoad(), road, target)) ||
				(direction < 0 && AreInOrder(target, road, selected_road_->GetRoad()))) {
				target = road;
			}
		}
		if (target) {
			RoadView* target_view = (RoadView*) target->GetView(game_);
			target_view->SelectFromCity(city->GetIndex());
			selected_road_->DeselectFromCity(city->GetIndex());
			selected_road_ = target_view;
		}
		return this;
	}	
}

bool CityView::AreInOrder(Road* road1, Road* road2, Road* road3) {
	std::vector<Road*> roads = {road1, road2, road3};
	for (int i = 0; i < 3; i++) {
		if (VectorMul(roads[0], roads[1]) > 0 && VectorMul(roads[1], roads[2]) > 0) {
			return true;
		}
		std::rotate(roads.begin(), roads.begin() + 1, roads.end());
	}
	return false;
}

double CityView::VectorMul(Road* road1, Road* road2) {
	std::pair<double, double> a = RoadToVector(road1);
	std::pair<double, double> b = RoadToVector(road2);
	return a.first * b.second - a.second * b.first;
}

std::pair<double, double> CityView::RoadToVector(Road* road) {
	City* city1 = (City*) node_;
	City* city2 = road->GetCities()[0]->GetIndex() == city1->GetIndex() ? road->GetCities()[1] : road->GetCities()[0];
	return {city2->x() - city1->x(), city2->y() - city1->y()};
}

bool CityView::IsRoadSelected() {
	return selected_road_ != 0;
}