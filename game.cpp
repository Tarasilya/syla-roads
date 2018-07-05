#include "game.h"
#include "painter.h"

Game::Game(Painter* painter) {
	painter_ = painter;
	InitMap();
}

Game::IdnitMap() {
	City* city_one = new City(200, 100, 0);
	City* city_two = new City(400, 100, 1);
	objects_.push_back(city_one);
	objects_.push_back(city_two);
	vector<City*> cities;
	cities.push_back(city_one);
	cities.push_back(city_two);
	objects_.push_back(new Road(cities))
}

void Game::Draw() {
	for (auto object: objects_) {
		object->Draw(painter_);
	}
}