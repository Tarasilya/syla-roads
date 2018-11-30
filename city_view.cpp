#include "city_view.h"
#include "painter.h"
#include "city.h"
#include "road_view.h"
#include "sizes.h"
#include "game.h"

#include <functional>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <sstream>

const double CLOSE_RANGE = 0.001;

CityView::CityView(Game* game, City* city) : game_(game), city_(city), selected_road_(0) {}

City* CityView::GetCity() {
	return city_;
}

RoadView* CityView::GetSelectedRoad()
{
	return selected_road_;
}

void CityView::Draw(Painter* painter) const {
	Color city_color = city_->GetOwner() == 0 ? NEUTRAL_CITY_COLOR : CITY_COLORS[city_->GetOwner()->GetId()];
	Circle city_image;
	

	if (!selected_by_.empty()) {
		Color outline_color = {0, 0, 0};
		for (int id : selected_by_) {
			outline_color.r += SELECTION_COLORS[id].r;
			outline_color.g += SELECTION_COLORS[id].g;
			outline_color.b += SELECTION_COLORS[id].b;

	    	std::stringstream ss;
	    	ss << city_->GetSyla() << std::endl << city_->GetWall();
			Text text = {id == 0 ? -1 : 0.55, -1, ss.str()};     	
			painter->Draw(text);
		}
		
		outline_color.r /= selected_by_.size();
		outline_color.g /= selected_by_.size();
		outline_color.b /= selected_by_.size();
		city_image = {city_->x(), city_->y(), CITY_RADIUS, city_color, CITY_RADIUS / 5, outline_color};
	}
	else {
		city_image = {city_->x(), city_->y(), CITY_RADIUS, city_color};
	}
    painter->Draw(city_image);
}

void CityView::RoadSelect() {
	if (selected_road_ != 0) {
		selected_road_->DeselectFromCity(city_->GetIndex());
		selected_road_ = 0;
	}
	else {
		const std::vector<Road*> roads = city_->GetRoads();
		if (roads.empty()) {
			return;
		}
		selected_road_ = (RoadView*) roads[0]->GetView(game_);
		selected_road_->SelectFromCity(city_->GetIndex());
	}
}

CityView* CityView::NextVertically(int direction) {
	if (selected_road_ == 0) {
		return NextCityVertically(direction);
	}
	else {
		return NextHorizontally(direction);
	}
}

CityView* CityView::NextHorizontally(int direction) {
	if (selected_road_ == 0) {
		return NextHorizontally(direction);
	}
	else {
		const std::vector<Road*> roads = city_->GetRoads();
		Road* target = 0;
		for (auto road: roads) {
			if (road == selected_road_->GetRoad()) {
				continue;
			}

			if (target == 0 || 
				(direction > 0 && AreInOrder(selected_road_->GetRoad(), road, target)) ||
				(direction < 0 && AreInOrder(target, road, selected_road_->GetRoad()))) {
				target = road;
			}
		}
		if (target) {
			RoadView* target_view = (RoadView*) target->GetView(game_);
			target_view->SelectFromCity(city_->GetIndex());
			selected_road_->DeselectFromCity(city_->GetIndex());
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
	City* city = road->GetCities()[0]->GetIndex() == city_->GetIndex() ? road->GetCities()[1] : road->GetCities()[0];
	return {city->x() - city_->x(), city->y() - city_->y()};
}

bool CityView::IsRoadSelected() {
	return selected_road_ != 0;
}

CityView* CityView::NextCityHorizontally(int direction) {
	return Next(
		[direction, this](City* a, City* b) {
			return IsInDirectionFromTo(a->x(), b->x(), direction);
		},
		[this](City* a, City* b) {
			return IsInCloseRange(a->y(), b->y());
		}
	);
}

CityView* CityView::NextCityVertically(int direction) {
	return Next(
		[direction, this](City* a, City* b) {
			return IsInDirectionFromTo(a->y(), b->y(), direction);
		},
		[this](City* a, City* b) {
			return IsInCloseRange(a->x(), b->x());
		}
	);
}

CityView* CityView::Next(const std::function<bool(City*, City*)>& less, const std::function<bool(City*, City*)>& same) {
	const std::vector<City*>& cities = game_->GetCities();

	CityView *same_line_target = 0, *any_line_target = 0;
	for (auto city: cities) {
		if (less(city_, city)) {
			UpdateIfBetter(any_line_target, city, less);
			if (same(city_, city)) {
				UpdateIfBetter(same_line_target, city, less);
			}
		}
	}

	if (same_line_target == 0) {
		return any_line_target == 0 ? this : any_line_target;
	}
	else {
		return same_line_target == 0 ? this : same_line_target;
	}

}

void CityView::UpdateIfBetter(CityView*& current, City* candidate, const std::function<bool(City*, City*)>& less) {
	if (current == 0 || less(candidate, current->GetCity())) {
		current = (CityView*) candidate->GetView(game_);
	}
}

bool CityView::IsInCloseRange(double base, double y) {
	return std::abs(base - y) < CLOSE_RANGE;
}

bool CityView::IsInDirectionFromTo(double from, double to, int direction) {
	return (to - from) * direction > 0;
}

void CityView::Select(int player_id) {
	selected_by_.insert(player_id);
}

void CityView::Deselect(int player_id) {
	selected_by_.erase(player_id);
}
