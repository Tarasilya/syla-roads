#include "road.h"
#include "enum.h"
#include "city.h"
#include "../painter.h"
#include "../shapes.h"

#include <iostream>

Road::Road(std::vector<City*> cities)
{
    cities_connected_ = cities;
}

void Road::Tick() {
	throw 1;
}

bool Road::ProcessClick(double x, double y) {
	throw 1;
}

void Road::Draw(Painter* painter)
{
    std::cerr << "drawing road" << std::endl;
    Color road_color = {0, 255, 255};
    double x1 = cities_connected_[0]->x();
    double y1 = cities_connected_[0]->y();
    double x2 = cities_connected_[1]->x();
    double y2 = cities_connected_[1]->y();
    Line road_image = {x1, y1, x2, y2, road_color};
    painter->Draw(road_image);
}


