#pragma once

#include "painter.h"

class Game {
private:
	Painter* painter_;
	vector<GameObject*> objects_;

	void InitMap();
	
public: 
	Game(Painter* painter);
	void Run();
	void Draw();
};