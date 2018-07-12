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
	void Draw(const Rectangle& rect);
	void Draw(const Circle& circle);
	void Draw(const Line& line);
};