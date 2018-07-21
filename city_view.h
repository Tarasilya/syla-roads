#pragma once

#include "game/city.h"
#include "node_view.h"

class Painter;

class CityView : public NodeView {
private:
	City* city_;
public:
	CityView(City* city);
	virtual void Draw(Painter* painter) const override;
	virtual Node* GetNode() const override;
};
