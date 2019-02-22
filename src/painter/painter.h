#pragma once

#include "shapes.h"

#include <SFML/Graphics.hpp>

#include <utility>

const Color ROAD_COLOR = {182, 180, 152};
const Color SELECTED_ROAD_COLOR = {17, 101, 8};
const Color BUILT_ROAD_COLOR =  {222, 212, 73};
const Color WAR_ROAD_COLOR =  {250, 250, 250};
const Color PLAYER_ONE_COLOR = {105, 140, 230, 127};
const Color PLAYER_TWO_COLOR = {210, 80, 40, 127 };
const std::vector<Color> PLAYER_COLORS = {PLAYER_ONE_COLOR, PLAYER_TWO_COLOR};
const Color SELECTION_COLORS [] = {{24, 84, 89}, {255, 37, 42}};
const Color CITY_COLORS [] = {{82, 194, 228}, {202, 27, 93}};
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