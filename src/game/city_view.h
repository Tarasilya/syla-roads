#pragma once

#include "object_view.h"

#include <functional>
#include <utility>
#include <set>

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

	CityView* Next(const std::function<bool(City*, City*)>& less, const std::function<bool(City*, City*)>& same);
	bool IsInDirectionFromTo(double from, double to, int direction);
	bool IsInCloseRange(double base, double y);
	void UpdateIfBetter(CityView*& current, City* candidate, const std::function<bool(City*, City*)>& less);
public:
	CityView(Game* game, City* city);
	City* GetCity();
	RoadView* GetSelectedRoad();
	void Draw(Painter* painter) const;
	void RoadSelect();
	bool IsRoadSelected();
	CityView* NextHorizontally(int direction);
	CityView* NextVertically(int direction);
	CityView* NextCityVertically(int direction);
	CityView* NextCityHorizontally(int direction);

	void Select(int player_id);
	void Deselect(int player_id);
};
