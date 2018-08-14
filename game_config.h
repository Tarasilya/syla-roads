#pragma once

#include "control_keys.h"

#include <SFML/Window.hpp>

#include <map>
#include <string>

class GameConfig {
private:
	std::vector<std::map<sf::Keyboard::Key, Control>> controls_;
public:
	GameConfig(std::string filename);
	std::map<sf::Keyboard::Key, Control> GetControls(int player_index);
};