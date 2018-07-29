#include "road_view.h"
#include "painter.h"
#include "road.h"
#include "city.h"

RoadView::RoadView(Road* road) : road_(road), selected_cities_(2) {}

const double THICKNESS = 0.03;

void RoadView::Draw(Painter* painter) const {
    Color road_color = ROAD_COLOR;
    double x1 = road_->GetCities()[0]->x();
    double y1 = road_->GetCities()[0]->y();
    double x4 = road_->GetCities()[1]->x();
    double y4 = road_->GetCities()[1]->y();
    double dx = (x4 - x1) /3;
    double dy = (y4 - y1) /3;
    double x2 = x1 + dx;
    double y2 = y1 + dy;
    double x3 = x2 + dx;
    double y3 = y2 + dy;
    Color color0 = selected_cities_[0] ? SELECTED_ROAD_COLOR : ROAD_COLOR;
    Color color1 = selected_cities_[1] ? SELECTED_ROAD_COLOR : ROAD_COLOR;
    Rectangle road_image_0 = {x1, y1 - THICKNESS / 2, x2, y2 + THICKNESS / 2, color0};
    Rectangle road_image_1 = {x3, y3 - THICKNESS / 2, x4, y4 + THICKNESS / 2, color1};
    Rectangle road_image_mid = {x2, y2 - THICKNESS / 2, x3, y3 + THICKNESS / 2, ROAD_COLOR};

    painter->Draw(road_image_0);	
    painter->Draw(road_image_1);	
    painter->Draw(road_image_mid);	
}

void RoadView::SelectFromCity(int city_id) {
	for (int i = 0; i < 2; i++) {
		if (road_->GetCities()[i]->GetIndex() == city_id) {
			selected_cities_[i] = true;
		}
	}
}

void RoadView::DeselectFromCity(int city_id) {
	for (int i = 0; i < 2; i++) {
		if (road_->GetCities()[i]->GetIndex() == city_id) {
			selected_cities_[i] = false;
		}
	}
}
