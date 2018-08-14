#include "game_config.h"

#include <fstream>

GameConfig::GameConfig(std::string filename) {
	controls_ = std::vector<std::map<sf::Keyboard::Key, Control>>(2);
	std::ifstream in(filename);
	for (int i = 0; i < 2; i++) {
		for (int j = 1; j <= NUMBER_OF_CONTROLS; j++) {
			int key;
			in >> key;
			controls_[i][(sf::Keyboard::Key) key] = (Control) j;
		}
	}
}

std::map<sf::Keyboard::Key, Control> GameConfig::GetControls(int player_index) {
	return controls_[player_index];
}