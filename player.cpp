#include "player.h"
#include "control_keys.h"
#include "game/node.h"

#include <iostream>

Player::Player(Game* game) : game_(game), focusedNode_(0) {
	controls_ = std::vector<sf::Keyboard::Key>(4);
	controls_[MOVE_LEFT] = sf::Keyboard::Left;
	controls_[MOVE_RIGHT] = sf::Keyboard::Right;
	controls_[MOVE_UP] = sf::Keyboard::Up;
	controls_[MOVE_DOWN] = sf::Keyboard::Down;	
}

bool Player::ProcessKey(sf::Keyboard::Key key) {
	std::cerr << "Player::ProcessKey " << key << std::endl;
	if (key == controls_[Control::MOVE_LEFT]) {
		MoveHorizontally(-1);
		return true;
	}
	if (key == controls_[Control::MOVE_RIGHT]) {
		MoveHorizontally(1);
		return true;
	}
	if (key == controls_[Control::MOVE_UP]) {
		MoveVertically(-1);
		return true;
	}
	if (key == controls_[Control::MOVE_DOWN]) {
		MoveVertically(1);
		return true;
	}
	return false;
}


void Player::MoveHorizontally(int direction) {
	std::cerr << "Player::MoveHorizontally " << direction << std::endl;
	const std::vector<Node*>& nodes = game_->GetNodes();
	if (focusedNode_ == 0) {
		focusedNode_ = (NodeView*) nodes[0]->GetView();
	}

	NodeView* target = 0;
	for (auto node: nodes) {
		if (node == focusedNode_->GetNode()) {
			continue;
		}
		if (IsInCloseRange(focusedNode_->GetNode()->y(), node->y()) && IsInDirectionFromTo(focusedNode_->GetNode(), node, direction)) {
			if (target == 0 || IsInDirectionFromTo(node, target->GetNode(), direction)) {
				target = (NodeView*) node->GetView();
			}
		}
	}
	if (target != 0) {
		focusedNode_->SetFocused(false);
		focusedNode_ = target;
		focusedNode_->SetFocused(true);
	}
}

void Player::MoveVertically(int direction) {
	throw 1;
}

bool Player::IsInCloseRange(int base, int y) {
	return true;
}

bool Player::IsInDirectionFromTo(Node* from, Node* to, int direction) {
	return (to->x() - from->x()) * direction > 0;
}