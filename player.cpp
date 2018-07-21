#include "player.h"
#include "control_keys.h"
#include "game/node.h"
#include "node_view.h"

#include <iostream>

Player::Player(NodeView* baseView) : baseView_(baseView), focusedView_(0) {
	controls_ = std::vector<sf::Keyboard::Key>(5);
	controls_[MOVE_LEFT] = sf::Keyboard::Left;
	controls_[MOVE_RIGHT] = sf::Keyboard::Right;
	controls_[MOVE_UP] = sf::Keyboard::Up;
	controls_[MOVE_DOWN] = sf::Keyboard::Down;
	controls_[SELECT] = sf::Keyboard::S;
}

bool Player::ProcessKey(sf::Keyboard::Key key) {
	std::cerr << "Player::ProcessKey " << key << std::endl;
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
			focusedView_->SetFocused(false);
			baseView_ = focusedView_;
			focusedView_ = 0;
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