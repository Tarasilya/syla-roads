#include "painter.h"

#include <SFML/Graphics.hpp>

#include <cmath>
#include <iostream>

Painter::Painter(sf::RenderWindow* window) {
	window_ = window;

	display_width_ = window_->getSize().x;
	display_height_ = window_->getSize().y;

	if (!font_.loadFromFile("font.ttf"))
	{
	    std::cerr << "cant load font!!" << std::endl;
	}	
}

void Painter::Draw(const Rectangle& rect) {
	int x1 = Transform(rect.x1, display_width_);
	int y1 = Transform(rect.y1, display_height_);
	int x2 = Transform(rect.x2, display_width_);
	int y2 = Transform(rect.y2, display_height_);

	sf::ConvexShape draw_rect;

	draw_rect.setPointCount(4);
	draw_rect.setFillColor(rect.color.ToSf());
	draw_rect.setPoint(0, sf::Vector2f(x1, y1));
	draw_rect.setPoint(1, sf::Vector2f(x1, y2));
	draw_rect.setPoint(2, sf::Vector2f(x2, y2));
	draw_rect.setPoint(3, sf::Vector2f(x2, y1));

	window_->draw(draw_rect);
}

void Painter::Draw(const Circle& circle) {
	int x = Transform(circle.x, display_width_);
	int y = Transform(circle.y, display_height_);
	int r = TransformSize(circle.r, std::min(display_width_, display_height_));
	int outline_r = TransformSize(circle.outline_r, std::min(display_width_, display_height_));
	sf::CircleShape draw_circle (r);

	draw_circle.setPosition(x - r, y - r);
	draw_circle.setFillColor(circle.color.ToSf());
	draw_circle.setOutlineThickness(outline_r);
	draw_circle.setOutlineColor(circle.outline_color.ToSf());

	window_->draw(draw_circle);
}

std::pair<double, double> Painter::ToLength(std::pair<double, double> vector, double length) {
	double initial = std::sqrt(vector.first*vector.first + vector.second*vector.second);
	return {vector.first * length / initial, vector.second * length / initial};
}


void Painter::Draw(const Line& line) {
	double dx = line.x2 - line.x1;
	double dy = line.y2 - line.y1;
	double dx1 = -dy;
	double dy1 = dx;
	std::pair<double, double> vec = ToLength({dx1, dy1}, line.thickness / 2);

	int x1 = Transform(line.x1 + vec.first, display_width_);
	int x2 = Transform(line.x2 + vec.first, display_width_);
	int x3 = Transform(line.x2 - vec.first, display_width_);
	int x4 = Transform(line.x1 - vec.first, display_width_);
	int y1 = Transform(line.y1 + vec.second, display_width_);
	int y2 = Transform(line.y2 + vec.second, display_width_);
	int y3 = Transform(line.y2 - vec.second, display_width_);
	int y4 = Transform(line.y1 - vec.second, display_width_);

	sf::ConvexShape draw_rect;
	draw_rect.setPointCount(4);
	draw_rect.setFillColor(line.color.ToSf());
	draw_rect.setPoint(0, sf::Vector2f(x1, y1));
	draw_rect.setPoint(1, sf::Vector2f(x2, y2));
	draw_rect.setPoint(2, sf::Vector2f(x3, y3));
	draw_rect.setPoint(3, sf::Vector2f(x4, y4));
	window_->draw(draw_rect);
}

void Painter::Draw(const Text& text) {
	int x = Transform(text.x, display_width_);
	int y = Transform(text.y, display_height_);
	sf::Text draw_text;
	draw_text.setString(text.text);
	draw_text.setFont(font_);
	draw_text.setCharacterSize(100);
	draw_text.setPosition(sf::Vector2f(x, y));
	draw_text.setColor(sf::Color::White);
	window_->draw(draw_text);
}



int Painter::Width() {
	return display_width_;
}

int Painter::Height() {
	return display_height_;
}

int Painter::Transform(double coord, int size) {
	return (coord + 1) / 2 * size;
}

int Painter::TransformSize(double size, int display) {
	return size / 2 * display;
}