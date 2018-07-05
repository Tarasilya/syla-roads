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
	draw_rect.setFillColor(sf::Color(255, 255, 255));
	draw_rect.setPoint(0, sf::Vector2f(rect.x1, rect.y1));
	draw_rect.setPoint(1, sf::Vector2f(rect.x1, rect.y2));
	draw_rect.setPoint(2, sf::Vector2f(rect.x2, rect.y2));
	draw_rect.setPoint(3, sf::Vector2f(rect.x2, rect.y1));

	window_->draw(draw_rect);
}

