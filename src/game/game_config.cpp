#include "game_config.h"

#include "utils/utils.h"

#include <iostream>
#include <fstream>

GameConfig::GameConfig() {
	std::ifstream in("config.txt");
	std::string name, value;
	while (in >> name) {
		in >> value;
		std::cerr << "read " << name << " " << value << std::endl;
		params_[name] = value;
	}
}

std::string GameConfig::GetString(std::string name) {
	return params_[name];
}

int GameConfig::GetInt(std::string name) {
	return std::stoi(params_[name]);
}

float GameConfig::GetFloat(std::string name) {
	return std::stof(params_[name]);
}

std::map<sf::Keyboard::Key, Control> GameConfig::GetControls(int player_index) {
	std::map<sf::Keyboard::Key, Control> controls_;
	std::string ids = utils::ToStr(player_index);
	controls_[GetKey("MOVE_LEFT" + ids)] = MOVE_LEFT;
	controls_[GetKey("MOVE_RIGHT" + ids)] = MOVE_RIGHT;
	controls_[GetKey("MOVE_UP" + ids)] = MOVE_UP;
	controls_[GetKey("MOVE_DOWN" + ids)] = MOVE_DOWN;
	controls_[GetKey("SELECT" + ids)] = SELECT;
	controls_[GetKey("ROAD_SELECT" + ids)] = ROAD_SELECT;
	controls_[GetKey("BUILD" + ids)] = BUILD;
	controls_[GetKey("ACT_LOW" + ids)] = ACT_LOW;
	controls_[GetKey("ACT_MEDIUM" + ids)] = ACT_MEDIUM;
	controls_[GetKey("ACT_HIGH" + ids)] = ACT_HIGH;
	controls_[GetKey("DECLARE_WAR" + ids)] = DECLARE_WAR;
	return controls_;
}

sf::Keyboard::Key GameConfig::GetKey(std::string name) {
	return ToSfKey(params_[name]);
}