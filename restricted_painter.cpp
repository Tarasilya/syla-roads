#include "restricted_painter.h"
#include "painter.h"

#include <iostream>

RestrictedPainter::RestrictedPainter(Painter* painter, Rectangle bound_rect) : Painter(*painter), bound_rect_(bound_rect) {}

void RestrictedPainter::Draw(const Rectangle& source_rect) {
	Rectangle rect = source_rect;
	rect.x1 += bound_rect_.x1;
	rect.y1 += bound_rect_.y1;
	rect.x2 += bound_rect_.x1;
	rect.y2 += bound_rect_.y1;

	if (rect.x2 > bound_rect_.x2 || rect.y2 > bound_rect_.y2) {
		return;
	}
	Painter::Draw(rect);
}

void RestrictedPainter::Draw(const Circle& source_circle) {
	std::cerr << "RestrictedPainter::Draw(Circle)" << std::endl;
	Circle circle = source_circle;
	circle.x += bound_rect_.x1;
	circle.y += bound_rect_.y1;

	if (circle.x + circle.r > bound_rect_.x2 || circle.y + circle.r > bound_rect_.y2) {
		return;
	}
	Painter::Draw(circle);
	std::cerr << "RestrictedPainter::Draw(Circle) finished" << std::endl;
}

void RestrictedPainter::Draw(const Line& source_line) {
	Line line = source_line;
	line.x1 += bound_rect_.x1;
	line.y1 += bound_rect_.y1;
	line.x2 += bound_rect_.x1;
	line.y2 += bound_rect_.y1;

	if (std::max(line.x1, line.x2) > bound_rect_.x2 || std::max(line.x2, line.y2) > bound_rect_.y2) {
		return;
	}
	Painter::Draw(line);	
}