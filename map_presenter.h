#pragma once

#include "presenter.h"
#include "map.h"
#include "painter.h"

#include <SFML/Window.hpp>



class MapPresenter : public Presenter {
private:
	Map map_;
	Painter* painter_;
public:
	MapPresenter(Controller* controller, Painter* painter, Map map);
	void Draw();
	void ProcessKey(sf::Keyboard::Key key);
	Map GetMap();
};