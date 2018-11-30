#pragma once

#include "object_view.h"
#include <utility>

class Painter;
class RoadView;
class City;
class Road;

class CityView : public ObjectView {
private:
	Game* game_;
	std::set<int> selected_by_;
	RoadView* selected_road_;
	City* city_;

	bool AreInOrder(Road* road1, Road* road2, Road* road3);
	double VectorMul(Road* road1, Road* road2);
	std::pair<double, double> RoadToVector(Road* road);

	NodeView* Next(const std::function<bool(Node*, Node*)>& less, const std::function<bool(Node*, Node*)>& same);
	bool IsInCloseRange(double base, double y);
	bool IsInDirectionFromTo(double from, double to, int direction);
	void UpdateIfBetter(NodeView*& current, Node* candidate, const std::function<bool(Node*, Node*)>& less);
public:
	CityView(Game* game, City* city);
	City* GetCity();
	RoadView* GetSelectedRoad();
	void Draw(Painter* painter) const;
	void RoadSelect();
	bool IsRoadSelected();
	NodeView* NextHorizontally(int direction);
	NodeView* NextVertically(int direction);
	NodeView* NextCityVertically(int direction);
	NodeView* NextCityHorizontally(int direction);

	void Select(int player_id);
	void Deselect(int player_id);
};
