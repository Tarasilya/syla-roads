#include "enum.h"
#include "city.h"
#include "road.h"
#include "player.h"
#include "control_keys.h"
#include "node.h"
#include "node_view.h"
#include "road_view.h"

#include <iostream>


Player::Player(std::map<sf::Keyboard::Key, Control> controls, NodeView* baseView, int id) 
	: baseView_(baseView), 
	focusedView_(0), 
	controls_(controls),
	id_(id) 
{
		std::cerr << "cr pl " << id_ << std::endl;
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
		std::cerr << "road selected" << std::endl;
		if (focusedView_ != 0) {
			focusedView_->RoadSelect();
		}
		return true;
	}

	if (focusedView_ != 0) {
		if (focusedView_->IsRoadSelected()){
			Road* current_road = focusedView_->GetSelectedRoad()->GetRoad();
			City* current_city = (City*) focusedView_->GetNode();
			if (current_city->GetOwner() == this){
				if (controls_[key] == BUILD && current_road->GetState() == CONSTRUCTION){
					current_city->SendCrew(5, current_road);
				}
				if (controls_[key] == ACT_LOW && current_road->GetState() == TRADE){
					std::cerr << "tr low" << std::endl;
					current_city->SendCrew(5, current_road);
				}

				if (controls_[key] == ACT_MEDIUM && current_road->GetState() != CONSTRUCTION){
					current_city->SendCrew(10, current_road);
				}
				if (controls_[key] == ACT_HIGH && current_road->GetState() == TRADE){
					std::cerr << "tr high" << std::endl;
					current_city->SendCrew(15, current_road);
				}
				if (controls_[key] == DECLARE_WAR && current_road->GetState() == TRADE){
					std::cerr << "war decl" << std::endl;
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

void Player::FocusOn(NodeView* view) {
	if (focusedView_) {
		focusedView_->Deselect(id_);
	}
	focusedView_ = view;
	focusedView_->Select(id_);
}