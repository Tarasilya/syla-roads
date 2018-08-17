#pragma once

#include "shapes.h"

#include <SFML/Graphics.hpp>

#include <utility>

const Color ROAD_COLOR = {200, 200, 200};
const Color SELECTED_ROAD_COLOR = {0, 255, 0};
const Color BUILT_ROAD = {0xE9, 0x1E, 0x63}; 
const Color PLAYER_ONE_COLOR = {0x88, 0x0E, 0x4F, 127};
const Color PLAYER_TWO_COLOR = {0x4A, 0x14, 0x8C, 127 };
const std::vector<Color> PLAYER_COLORS = {PLAYER_ONE_COLOR, PLAYER_TWO_COLOR};
const Color SELECTION_COLORS [] = {{0xF4, 0x43, 0x36}, {0x21, 0x96, 0xF3}};
const Color CITY_COLORS [] = {{0xF0, 0x62, 0x92}, {0x81, 0xD4, 0xFA}};
const Color NEUTRAL_CITY_COLOR = {0x21, 0x21, 0x21};

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