#include "painter.h"

#include <SFML/Graphics.hpp>

Painter::Painter(sf::RenderWindow* window) {
	window_ = window;

	window_width_ = window_->getSize().x;
	window_height_ = window_->getSize().y;
}

void Painter::Draw(const Rectangle& rect) {
	sf::ConvexShape draw_rect;

	draw_rect.setPointCount(4);
	draw_rect.setFillColor(sf::Color(rect.color.r, rect.color.g, rect.color.b));
	draw_rect.setPoint(0, sf::Vector2f(rect.x1, rect.y1));
	draw_rect.setPoint(1, sf::Vector2f(rect.x1, rect.y2));
	draw_rect.setPoint(2, sf::Vector2f(rect.x2, rect.y2));
	draw_rect.setPoint(3, sf::Vector2f(rect.x2, rect.y1));

	window_->draw(draw_rect);
}

void Painter::Draw(const Circle& circle) {
	sf::CircleShape draw_circle (circle.r);

	draw_circle.setPosition(circle.x - circle.r, circle.y - circle.r);
	draw_circle.setFillColor(sf::Color(circle.color.r, circle.color.g, circle.color.b));

	window_->draw(draw_circle);
}

void Painter::Draw(const Line& line) {
	sf::Vertex draw_line[] =
	{
	    sf::Vertex(sf::Vector2f(line.x1, line.y1)),
	    sf::Vertex(sf::Vector2f(line.x2, line.y2))
	};

	window_->draw(draw_line, 2, sf::Lines);
}