#include "city.h"
#include "../painter.h"
#include "../shapes.h"

City::City(int x_coord, int y_coord, int index)
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

bool City::ProcessClick(int x, int y) {
	throw 1;
}

void City::Draw(Painter* painter)
{
    Color city_color = {255, 0, 0};
    Circle city_image = {x_, y_, 10, city_color};
    painter->Draw(city_image);
}

int City::x() {
	return x_;
}

int City::y() {
	return y_;
}