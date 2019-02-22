#pragma once

#include "control_keys.h"

#include <SFML/Window.hpp>

#include <map>
#include <string>

class GameConfig {
public:
    static GameConfig& getInstance()
    {
        static GameConfig instance; 
        return instance;
    }
private:
    GameConfig();

	std::map<std::string, std::string> params_;

	sf::Keyboard::Key GetKey(std::string);
public:
	std::map<sf::Keyboard::Key, Control> GetControls(int player_index);
	std::string GetString(std::string name);
    int GetInt(std::string name);
    float GetFloat(std::string name);

public:
    GameConfig(GameConfig const&) = delete;
    void operator=(GameConfig const&) = delete;
};
