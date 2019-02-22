#pragma once

#include <SFML/Window.hpp>

#include <string>

enum Control {
	NOTHING = 0,
	MOVE_LEFT, 
	MOVE_RIGHT,
	MOVE_UP,
	MOVE_DOWN,
	SELECT,
	ROAD_SELECT,

	BUILD,
	ACT_LOW,
	ACT_MEDIUM,
	ACT_HIGH,
	DECLARE_WAR,
};

sf::Keyboard::Key ToSfKey(std::string);
