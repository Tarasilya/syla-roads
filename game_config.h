#pragma once

#include "control_keys.h"

#include <SFML/Window.hpp>

#include <map>
#include <string>

class GameConfig {
private:
	std::map<std::string, std::string> params_;

	sf::Keyboard::Key GetKey(std::string);
public:
	GameConfig(std::string filename);
	std::map<sf::Keyboard::Key, Control> GetControls(int player_index);
	std::string GetString(std::string name);
};