#pragma once

#include "game_object.h"

class Painter;

class ObjectView {
public:
	virtual void Draw(Painter* painter) const = 0;
};