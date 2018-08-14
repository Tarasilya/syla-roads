#include "player.h"
#include "control_keys.h"
#include "node.h"
#include "node_view.h"

#include <iostream>

Player::Player(std::map<sf::Keyboard::Key, Control> controls, NodeView* baseView) : baseView_(baseView), focusedView_(0), controls_(controls) {
}

bool Player::ProcessKey(sf::Keyboard::Key key) {
	if (key == controls_[Control::MOVE_LEFT]) {
		if (focusedView_) {
			FocusOn(focusedView_->NextHorizontally(-1));
		}
		return true;
	}
	if (key == controls_[Control::MOVE_RIGHT]) {
		if (focusedView_) {
			FocusOn(focusedView_->NextHorizontally(1));
		}
		return true;
	}
	if (key == controls_[Control::MOVE_UP]) {
		if (focusedView_) {
			FocusOn(focusedView_->NextVertically(-1));
		}
		return true;
	}
	if (key == controls_[Control::MOVE_DOWN]) {
		if (focusedView_) {
			FocusOn(focusedView_->NextVertically(1));
		}
		return true;
	}
	if (key == controls_[SELECT]) {
		if (focusedView_ == 0) {
			FocusOn(baseView_);
		}
		else {
			if (focusedView_->IsRoadSelected()) {
				focusedView_->RoadSelect();
			}
			else {
				focusedView_->SetFocused(false);
				baseView_ = focusedView_;
				focusedView_ = 0;
			}
		}
		return true;
	}
	if (key == controls_[ROAD_SELECT]) {
		std::cerr << "road selected" << std::endl;
		if (focusedView_ != 0) {
			focusedView_->RoadSelect();
		}
		return true;
	}
	return false;
}

void Player::FocusOn(NodeView* view) {
	if (focusedView_) {
		focusedView_->SetFocused(false);
	}
	focusedView_ = view;
	focusedView_->SetFocused(true);
}