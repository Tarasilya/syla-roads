#include "city_view.h"
#include "painter.h"
#include "city.h"
#include "road_view.h"

#include <iostream>

CityView::CityView(Game* game, City* city) : NodeView(game, city), selected_road_(0) {}

void CityView::Draw(Painter* painter) const {
    Color city_color = {255, 255 * focused_, 0};
    City* city = (City*) node_;
    Circle city_image = {city->x(), city->y(), 0.1, city_color};
    painter->Draw(city_image);
}

void CityView::RoadSelect() {
	std::cerr << "CityView::RoadSelect" << std::endl;
	City* city = (City*) node_;
	if (selected_road_ != 0) {
		selected_road_->DeselectFromCity(city->GetIndex());
		selected_road_ = 0;
	}
	else {
		const std::vector<Road*> roads = city->GetRoads();
		if (roads.empty()) {
			std::cerr << "roads empty??" << std::endl;
			return;
		}
		selected_road_ = (RoadView*) roads[0]->GetView(game_);
		selected_road_->SelectFromCity(city->GetIndex());
	}
}

bool CityView::IsRoadSelected() {
	return selected_road_ != 0;
}