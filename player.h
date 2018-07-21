#pragma once

#include <SFML/Window.hpp>

class NodeView;

class Player {
private:
	std::vector<sf::Keyboard::Key> controls_;
	NodeView* focusedView_;
	NodeView* baseView_;

	void FocusOn(NodeView* view);
public:
	Player(NodeView* baseView);

	bool ProcessKey(sf::Keyboard::Key key);
};