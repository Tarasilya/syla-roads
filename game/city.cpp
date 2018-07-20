#include "city.h"
#include "../painter.h"
#include "../shapes.h"

City::City(double x_coord, double y_coord, int index)
{
    x_ = x_coord;
    y_ = y_coord;
    city_index_ = index;
    syla_ = 0;
    capacity_ = 100;
    wall_ = 100;
}

void City::Tick() {
	throw 1;
}

void City::Draw(Painter* painter)
{
    Color city_color = {255, 0, 0};
    Circle city_image = {x_, y_, 0.1, city_color};
    painter->Draw(city_image);
}

double City::x() {
	return x_;
}

double City::y() {
	return y_;
}