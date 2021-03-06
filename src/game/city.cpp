#include "road.h"
#include "city.h"
#include "city_view.h"

#include "painter/shapes.h"
#include "painter/painter.h"

#include <algorithm>
#include <sstream>
#include <iostream>

// Vynosim konstanty:

City::City(double x_coord, double y_coord, int index, int player_id) :
    index_(index), syla_reserve_(200), syla_capacity_(200), wall_(100), player_id_(player_id), owner_(0), texas_tax_collection_rate_(0.1)
{
    x_ = x_coord;
    y_ = y_coord;
    view_ = 0;
}

int City::GetPlayerId() {
    return player_id_;
}

void City::AddRoad(Road* road) {
    roads_.push_back(road);     
}

void City::Tick(double tick_time) {
    AcquireSyla(tick_time*texas_tax_collection_rate_);
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

double City::GetWall() {
    return wall_;
}

void City::DamageWall(double syla_rate){
	wall_ -= syla_rate;
}

void City::AcquireSyla(double syla){
	syla_reserve_ = std::min(syla_reserve_ + syla, syla_capacity_);
}

double City::GetSyla()
{    
    return syla_reserve_;
}

void City::SendCrew(double syla_rate, Road* target_road)
{
	target_road->SetSylaInflux(index_, syla_rate);
}

void City::ChangeOwner(Player* new_owner)
{
    owner_ = new_owner;
    player_id_ = new_owner->GetId();
}

void City::ResetCapture()
{
    wall_ = 100;
    syla_reserve_ = 100;
    for (auto road: roads_) {
        road->ResetToTrade();
    }
}

bool City::LoseSyla(double syla)
{
    if (syla <= syla_reserve_)
    {
        syla_reserve_ -= syla;
        return true;
    }
    else
    {
        return false;
    }
}

const std::vector<Road*>& City::GetRoads() {
	return roads_;
}

double City::x() {
    return x_;
}

double City::y() {
    return y_;
}

Player* City::GetOwner()
{
    return owner_;
}
