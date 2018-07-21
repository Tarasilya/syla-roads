#pragma once

#include "painter.h"
#include "game/game_object.h"

class Game {
private:
	Painter* painter_;
	std::vector<GameObject*> objects_;
	double total_time_;
	int seconds_;
	void InitMap();
	
public: 
	Game(Painter* painter);
	void Run();
	void Redraw();
	void ProcessKey(sf::Keyboard::Key key);
	void Tick(double dt);
};