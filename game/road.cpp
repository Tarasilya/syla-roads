#include "road.h"
#include "enum.h"
#include "city.h"
#include "../painter.h"
#include "../shapes.h"

Road::Road(std::vector<City*> cities)
{
    cities_connected_ = cities;
}

void Road::Draw()
{
    Color road_color(0, 255, 255);
    x1 = cities_connected_[0]->x_;
    y1 = cities_connected_[0]->y_;
    x2 = cities_connected_[1]->x_;
    y2 = cities_connected_[1]->y_;
    Line road_image(x1, y1, x2, y2, Color);
    Painter.draw(road_image);
}


