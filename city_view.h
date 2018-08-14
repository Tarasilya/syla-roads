#pragma once

#include "node_view.h"
#include <utility>

class Painter;
class RoadView;
class City;
class Road;

class CityView : public NodeView {
private:
	RoadView* selected_road_;
	City* selected_city_;

	bool AreInOrder(Road* road1, Road* road2, Road* road3);
	double VectorMul(Road* road1, Road* road2);
	std::pair<double, double> RoadToVector(Road* road);
public:
	CityView(Game* game, City* city);
	City* GetSelectedCity();
	virtual RoadView* GetSelectedRoad() override;
	virtual void Draw(Painter* painter) const override;
	virtual void RoadSelect() override;
	virtual bool IsRoadSelected() override;
	virtual NodeView* NextHorizontally(int direction) override;
	virtual NodeView* NextVertically(int direction) override;
};
