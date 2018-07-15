#pragma once

#include "painter.h"
#include "game/game_object.h"
#include <SFML/Window.hpp>

class Map;

class Game {
private:
	Painter* painter_;
	std::vector<GameObject*> objects_;

	void InitMap();

public:
	Game(Painter* painter);
	Game(Painter* painter, Map map);
	void ProcessKey(sf::Keyboard::Key key);
	void Draw();
	void Pause();
};
