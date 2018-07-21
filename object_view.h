#pragma once

class Painter;

class ObjectView {
public:
	virtual void Draw(Painter* painter) const = 0;
};