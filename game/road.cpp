#include "road.h"
#include "enum.h"
#include "city.h"
#include "../painter.h"
#include "../shapes.h"
#include "../road_view.h"

Road::Road(std::vector<City*> cities)
{
	view_ = 0;
    cities_connected_ = cities;
}

void Road::Tick() {
	throw 1;
}

ObjectView* Road::GetView(Game* game) {
	if (view_ == 0) {
		view_ = new RoadView(this);
	}
	return view_;
}

const std::vector<City*>& Road::GetCities() {
	return cities_connected_;
}