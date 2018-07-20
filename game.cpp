#include "game.h"
#include "painter.h"
#include "game/road.h"
#include "game/city.h"
#include "game/game_object.h"

Game::Game(Painter* painter) {
	painter_ = painter;
	InitMap();
}

void Game::InitMap() {
	City* city_one = new City(-0.5, -0.5, 0);
	City* city_two = new City(0.5, 0.5, 1);
	objects_.push_back(city_one);
	objects_.push_back(city_two);
	std::vector<City*> cities;
	cities.push_back(city_one);
	cities.push_back(city_two);
	objects_.push_back(new Road(cities));
}

void Game::Draw() {
	for (auto object: objects_) {
		object->Draw(painter_);
	}
}

void Game::ProcessKey(sf::Keyboard::Key key) {
}