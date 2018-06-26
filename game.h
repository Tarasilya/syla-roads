#pragma once

#include "painter.h"

class Game {
private:
	Painter* painter_;
public: 
	Game(Painter* painter);
	void run();
	void redraw();
};