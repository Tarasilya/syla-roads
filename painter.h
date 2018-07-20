#pragma once

#include "shapes.h"

#include <SFML/Graphics.hpp>


class Painter {
private:
	sf::RenderWindow* window_;
	int display_width_;
	int display_height_;

	int Transform(double corrd, int display_size);
	int TransformSize(double size, int display);
public:
	Painter(sf::RenderWindow* window);
	void Draw(const Rectangle& rect);
	void Draw(const Circle& circle);
	void Draw(const Line& line);

	virtual int Width();
	virtual int Height();
};