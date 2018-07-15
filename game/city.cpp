#include "city.h"
#include "../painter.h"
#include "../shapes.h"
#include "parameters.h"

#include <iostream>

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

bool City::ProcessClick(double x, double y) {
	throw 1;
}

double Parameters::CITY_RADIUS;
void City::Draw(Painter* painter)
{
    std::cerr << "drawing city" << std::endl;
    Color city_color = {255, 0, 0};
    std::cerr << "1" << std::endl;
    Circle city_image = {x_, y_, Parameters::CITY_RADIUS, city_color};
    std::cerr << "2" << std::endl;
    std::cerr << painter << std::endl;
    painter->Draw(city_image);
    std::cerr << "finished drawing city" << std::endl;
}

double City::x() {
	return x_;
}

double City::y() {
	return y_;
}