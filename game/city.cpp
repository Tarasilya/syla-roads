#include "city.h"
#include "../painter.h"
#include "../shapes.h"
#include <algorithm>

City::City(int x_coord, int y_coord, int index)
{
    x_ = x_coord;
    y_ = y_coord;
    city_index_ = index;
    syla_ = 1000;
    capacity_ = 100;
    wall_ = 100;
}

int City::CalculateSylaOutlux()
{
    int num_roads = roads_.size();
    int outflux = 0;
    for (int i = 0; i < num_roads; i++)
    {
        outflux += roads_[i]->CityExpense();
    }
}

void City::Tick(double dt) {
	
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

void City::DamageWall(int syla_rate){
	wall_ -= syla_rate;
}

void City::AcquireSyla(int syla){
	syla_reserve_ = std::min(syla_reserve_ + syla, syla_capacity_);		
}

void City::SendCrew(int syla_rate, Road* target_road)
{
	target_road->SeSylaInflux(city_inde, syla_rate);
}