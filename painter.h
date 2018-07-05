#pragma once

#include "shapes.h"

#include <SFML/Graphics.hpp>

class Painter {
private:
	sf::RenderWindow* window_;
	int window_width_;
	int window_height_;
public:
	Painter(sf::RenderWindow* window);
	void draw(const Rectangle& rect);
	void draw(const Circle& circle);
	void draw(const Line& line);
};