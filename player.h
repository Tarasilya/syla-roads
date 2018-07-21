#pragma once

#include "object_view.h"
#include "node_view.h"
#include "game.h"

#include <SFML/Window.hpp>

class Node;

class Player {
private:
	Game* game_;
	std::vector<sf::Keyboard::Key> controls_;
	NodeView* focusedNode_;

	void MoveHorizontally(int direction);
	void MoveVertically(int direction);

	bool IsInCloseRange(int base, int y);
	bool IsInDirectionFromTo(Node* from, Node* to, int direction);
public:
	Player(Game* game);

	bool ProcessKey(sf::Keyboard::Key key);
};