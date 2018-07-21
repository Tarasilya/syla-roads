#pragma once

#include "game/road.h"
#include "object_view.h"

class Painter;

class RoadView : public ObjectView {
private:
	Road* road_;
public:
	RoadView(Road* road);
	virtual void Draw(Painter* painter) const override;
};
