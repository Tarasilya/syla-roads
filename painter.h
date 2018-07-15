#pragma once

#include "shapes.h"

#include <SFML/Graphics.hpp>


class Painter {
private:
	sf::RenderWindow* window_;
	int display_width_;
	int display_height_;

	int Transform(int coord, int size);
public:
	Painter(sf::RenderWindow* window);
	virtual void Draw(const Rectangle& rect);
	virtual void Draw(const Circle& circle);
	virtual void Draw(const Line& line);

	int Width();
	int Height();
};