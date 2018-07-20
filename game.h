#pragma once

#include "painter.h"
#include "game/game_object.h"

class Game {
private:
	Painter* painter_;
	std::vector<GameObject*> objects_;

	void InitMap();
	
public: 
	Game(Painter* painter);
	void Run();
	void Draw();
	void ProcessKey(sf::Keyboard::Key key);
};