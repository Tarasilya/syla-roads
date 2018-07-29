#include "road.h"
#include "city.h"
#include "painter.h"
#include "shapes.h"
#include "city_view.h"

#include <algorithm>
#include <sstream>
#include <iostream>

City::City(double x_coord, double y_coord, int index) :
    index_(index), syla_reserve_(1000), syla_capacity_(1000), wall_(100)
{
    x_ = x_coord;
    y_ = y_coord;
    view_ = 0;
}

void City::AddRoad(Road* road) {
    roads_.push_back(road);     
}

City::operator std::string() const
{
    std::stringstream ss;
    ss << "City index: " << index_ << "\nSyla reserve: " << syla_reserve_ << "\nWall :" <<  wall_ << "\n";
    return ss.str();
}



void City::Tick(double tick_time) {

}

ObjectView* City::GetView(Game* game) {
	if (view_ == 0) {
		view_ = new CityView(game, this);
	}
	return view_;
}

int City::GetIndex() {
	return index_;
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
	target_road->SetSylaInflux(index_, syla_rate);
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

const std::vector<Road*>& City::GetRoads() {
	return roads_;
}
