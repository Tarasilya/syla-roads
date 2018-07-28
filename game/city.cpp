#include "road.h"
#include "city.h"
#include "../painter.h"
#include "../shapes.h"
#include <algorithm>
#include <sstream>
#include <iostream>


City::City(double x_coord, double y_coord, int index)
{
    x_ = x_coord;
    y_ = y_coord;
    city_index_ = index;
    syla_reserve_ = 1000;
    syla_capacity_ = 1000;
    wall_ = 100;
}

City::operator std::string() const
{
    std::stringstream ss;
    ss << "City index: " << city_index_ << "\nSyla reserve: " << syla_reserve_ << "\nWall :" <<  wall_ << "\n";
    return ss.str();
}



void City::Tick(double tick_time) {

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

void City::DamageWall(double syla_rate){
	wall_ -= syla_rate;
}

void City::AcquireSyla(double syla){
	syla_reserve_ = std::min(syla_reserve_ + syla, syla_capacity_);
}

void City::SendCrew(double syla_rate, Road* target_road)
{
    std::cout << "SendCrew: " << syla_rate << "\n";
	target_road->SetSylaInflux(city_index_, syla_rate);
}

bool City::LoseSyla(double syla)
{
    if (syla <= syla_reserve_)
    {
        syla_reserve_ -= syla;
        return 1;
    }
    else
    {
        return 0;
    }
}
