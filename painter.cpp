#include "painter.h"

#include <SFML/Graphics.hpp>

#include <cmath>

Painter::Painter(sf::RenderWindow* window) {
	window_ = window;

	display_width_ = window_->getSize().x;
	display_height_ = window_->getSize().y;
}

void Painter::Draw(const Rectangle& rect) {
	int x1 = Transform(rect.x1, display_width_);
	int y1 = Transform(rect.y1, display_height_);
	int x2 = Transform(rect.x2, display_width_);
	int y2 = Transform(rect.y2, display_height_);

	sf::ConvexShape draw_rect;

	draw_rect.setPointCount(4);
	draw_rect.setFillColor(sf::Color(rect.color.r, rect.color.g, rect.color.b));
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
	sf::CircleShape draw_circle (r);

	draw_circle.setPosition(x - r, y - r);
	draw_circle.setFillColor(sf::Color(circle.color.r, circle.color.g, circle.color.b));

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

	double x1 = Transform(line.x1 + vec.first, display_width_);
	double x2 = Transform(line.x2 + vec.first, display_width_);
	double x3 = Transform(line.x2 - vec.first, display_width_);
	double x4 = Transform(line.x1 - vec.first, display_width_);
	double y1 = Transform(line.y1 + vec.second, display_width_);
	double y2 = Transform(line.y2 + vec.second, display_width_);
	double y3 = Transform(line.y2 - vec.second, display_width_);
	double y4 = Transform(line.y1 - vec.second, display_width_);

	sf::ConvexShape draw_rect;
	draw_rect.setPointCount(4);
	draw_rect.setFillColor(sf::Color(line.color.r, line.color.g, line.color.b));
	draw_rect.setPoint(0, sf::Vector2f(x1, y1));
	draw_rect.setPoint(1, sf::Vector2f(x2, y2));
	draw_rect.setPoint(2, sf::Vector2f(x3, y3));
	draw_rect.setPoint(3, sf::Vector2f(x4, y4));
	window_->draw(draw_rect);
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