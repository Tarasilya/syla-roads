#include "road.h"
#include "enum.h"
#include "city.h"
#include "../painter.h"
#include "../shapes.h"

Road::Road(std::vector<City*> cities)
{
    cities_connected_ = cities;
}

void Road::Tick() {
	throw 1;
}

bool Road::ProcessClick(int x, int y) {
	throw 1;
}

void Road::Draw(Painter* painter)
{
    Color road_color = {0, 255, 255};
    int x1 = cities_connected_[0]->x();
    int y1 = cities_connected_[0]->y();
    int x2 = cities_connected_[1]->x();
    int y2 = cities_connected_[1]->y();
    Line road_image = {x1, y1, x2, y2, road_color};
    painter->Draw(road_image);
}


