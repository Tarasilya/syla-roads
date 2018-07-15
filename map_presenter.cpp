#include "map_presenter.h"
#include "game/game_object.h"
#include "map.h"

#include <iostream>

MapPresenter::MapPresenter(Controller* controller, Painter* painter, Map map): Presenter(controller, painter), map_(map) {
	std::cerr << "MapPresenter constructed" << std::endl;
}

void MapPresenter::Draw() {
	const std::vector<GameObject*>& objects = map_.GetObjects();
	std::cerr << "map_.GetObjects() done" << std::endl;
	for (auto object : objects) {
		object->Draw(painter_);
	}
	std::cerr << "MapPresenter::Draw() done" << std::endl;	
}

void MapPresenter::ProcessKey(sf::Keyboard::Key key) {}

Map MapPresenter::GetMap() {
	return map_;
}