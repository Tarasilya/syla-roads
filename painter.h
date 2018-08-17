#pragma once

#include "shapes.h"

#include <SFML/Graphics.hpp>

#include <utility>

const Color ROAD_COLOR = {200, 200, 200};
const Color SELECTED_ROAD_COLOR = {0, 255, 0};
const Color BUILT_ROAD = {0xE9, 0x1E, 0x63}; 
const Color PLAYER_ONE_COLOR = {0x88, 0x0E, 0x4F};
const Color PLAYER_TWO_COLOR = {0x4A, 0x14, 0x8C};
const std::vector<Color> PLAYER_COLORS = {PLAYER_ONE_COLOR, PLAYER_TWO_COLOR};
class Painter {
private:
	sf::RenderWindow* window_;
	sf::Font font_;
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