#pragma once

#include "game/city.h"
#include "node_view.h"

class Painter;

class CityView : public NodeView {
public:
	CityView(Game* game, City* city);
	virtual void Draw(Painter* painter) const override;
};
