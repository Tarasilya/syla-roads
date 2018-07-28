#include "city.h"
#include "../painter.h"
#include "../shapes.h"
#include "../city_view.h"

City::City(double x_coord, double y_coord, int index)
{
	view_ = 0;
    x_ = x_coord;
    y_ = y_coord;
    index_ = index;
    syla_ = 0;
    capacity_ = 100;
    wall_ = 100;
}

void City::Tick() {
	throw 1;
}

ObjectView* City::GetView(Game* game) {
	if (view_ == 0) {
		view_ = new CityView(game, this);
	}
	return view_;
}

int City::GetIndex() {
	return index_;
}

const std::vector<Road*>& City::GetRoads() {
	return roads_;
}