#pragma once

#include "node_view.h"

class Painter;
class RoadView;
class City;

class CityView : public NodeView {
private:
	RoadView* selected_road_;
public:
	CityView(Game* game, City* city);
	virtual void Draw(Painter* painter) const override;
	virtual void RoadSelect() override;
	virtual bool IsRoadSelected() override;
};
