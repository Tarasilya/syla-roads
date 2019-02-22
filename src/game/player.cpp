#include "enum.h"
#include "city.h"
#include "road.h"
#include "player.h"
#include "control_keys.h"
#include "road_view.h"
#include "city_view.h"

#include <iostream>

Player::Player(std::map<sf::Keyboard::Key, Control> controls, CityView* baseView, int id) 
	: baseView_(baseView), 
	focusedView_(0), 
	controls_(controls),
	id_(id) 
{
}

int Player::GetId() {
	return id_;
}

bool Player::ProcessKey(sf::Keyboard::Key key) {
	if (controls_[key] == 0){
		return false;
	}
	switch (controls_[key]){

	case MOVE_LEFT: 
		if (focusedView_) {
			FocusOn(focusedView_->NextHorizontally(-1));
		}
		return true;

	case MOVE_RIGHT:
		if (focusedView_) {
			FocusOn(focusedView_->NextHorizontally(1));
		}
		return true;
	
	case MOVE_UP:
		if (focusedView_) {
			FocusOn(focusedView_->NextVertically(-1));
		}
		return true;
	
	case MOVE_DOWN:
		if (focusedView_) {
			FocusOn(focusedView_->NextVertically(1));
		}
		return true;
	
	case SELECT:
		if (focusedView_ == 0) {
			FocusOn(baseView_);
		}
		else {
			if (focusedView_->IsRoadSelected()) {
				focusedView_->RoadSelect();
			}
			else {
				focusedView_->Deselect(id_);
				baseView_ = focusedView_;
				focusedView_ = 0;
			}
		}
		return true;
	
	case ROAD_SELECT:
		if (focusedView_ != 0) {
			focusedView_->RoadSelect();
		}
		return true;
	}

	if (focusedView_ != 0) {
		if (focusedView_->IsRoadSelected()){
			Road* current_road = focusedView_->GetSelectedRoad()->GetRoad();
			City* current_city = focusedView_->GetCity();
			if (current_city->GetOwner() == this){
				if (controls_[key] == BUILD && current_road->GetState() == CONSTRUCTION){
					current_city->SendCrew(5, current_road);
				}
				if (controls_[key] == ACT_LOW && current_road->GetState() == TRADE){
					current_city->SendCrew(5, current_road);
				}

				if (controls_[key] == ACT_MEDIUM && current_road->GetState() != CONSTRUCTION){
					current_city->SendCrew(10, current_road);
				}
				if (controls_[key] == ACT_HIGH && current_road->GetState() == TRADE){
					current_city->SendCrew(15, current_road);
				}
				if (controls_[key] == DECLARE_WAR && current_road->GetState() == TRADE 
					&& current_road->GetCities()[0]->GetOwner() != current_road->GetCities()[1]->GetOwner()){
					current_road->InitiateWar();
				}
				if (controls_[key] == ACT_LOW && current_road->GetState() == WAR){
					current_city->SendCrew(5, current_road);
				}
				if (controls_[key] == ACT_HIGH && current_road->GetState() == WAR){
					current_city->SendCrew(15, current_road);
				}
			}
		}
	}
	return true;

}

void Player::FocusOn(CityView* view) {
	if (focusedView_) {
		focusedView_->Deselect(id_);
	}
	focusedView_ = view;
	focusedView_->Select(id_);
}