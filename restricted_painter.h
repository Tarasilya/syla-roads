#pragma once

#include "painter.h"
class Rectangle;
class Circle;
class Line;

class RestrictedPainter : public Painter {
private:
	Rectangle bound_rect_;

public:
	RestrictedPainter(Painter* painter, Rectangle bound_rect);

	virtual void Draw(const Rectangle& rect) override;
	virtual void Draw(const Circle& circle) override;
	virtual void Draw(const Line& line) override;
};