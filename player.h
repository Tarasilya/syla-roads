#pragma once

#include "control_keys.h"

#include <SFML/Window.hpp>

#include <map>
class NodeView;

class Player {
private:
	int id_;
	std::map<sf::Keyboard::Key, Control> controls_;
	NodeView* focusedView_;
	NodeView* baseView_;

	void FocusOn(NodeView* view);
public:
	Player(std::map<sf::Keyboard::Key, Control> controls, NodeView* baseView, int id);

	bool ProcessKey(sf::Keyboard::Key key);
	int GetId();
};