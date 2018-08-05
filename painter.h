#pragma once

#include "shapes.h"

#include <SFML/Graphics.hpp>

#include <utility>

const Color ROAD_COLOR = {200, 200, 200};
const Color SELECTED_ROAD_COLOR = {0, 255, 0};

class Painter {
private:
	sf::RenderWindow* window_;
	int display_width_;
	int display_height_;

	int Transform(double corrd, int display_size);
	int TransformSize(double size, int display);
	std::pair<double, double> ToLength(std::pair<double, double> vector, double length);
public:
	Painter(sf::RenderWindow* window);
	void Draw(const Rectangle& rect);
	void Draw(const Circle& circle);
	void Draw(const Line& line);
	void Draw(const Text& test);

	virtual int Width();
	virtual int Height();
};