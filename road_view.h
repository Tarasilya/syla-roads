#pragma once

#include "road.h"
#include "object_view.h"

class Painter;

class RoadView : public ObjectView {
private:
	Road* road_;
	std::vector<bool> selected_cities_;
public:
	RoadView(Road* road);
	virtual void Draw(Painter* painter) const override;

	void SelectFromCity(int city_id);
	void DeselectFromCity(int city_id);
};
