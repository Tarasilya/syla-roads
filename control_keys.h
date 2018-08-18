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
	TRADE_LOW,
	TRADE_HIGH,
	DECLARE_WAR,
	COMBAT_LOW,
	COMBAT_HIGH,
};

sf::Keyboard::Key ToSfKey(std::string);