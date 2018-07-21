#include "game.h"
#include "painter.h"
#include "game/road.h"
#include "game/city.h"
#include "game/game_object.h"
#include "game/node.h"
#include "player.h"

Game::Game(Painter* painter) {
	painter_ = painter;
	InitMap();
	InitViews();
}

void Game::InitMap() {
	City* city_one = new City(-0.75, 0, 0);
	City* city_two = new City(-0.25, 0, 1);
	City* city_three = new City(0.25, 0, 2);
	City* city_four = new City(0.75, 0, 3);
	objects_.push_back(city_one);
	objects_.push_back(city_two);
	objects_.push_back(city_three);
	objects_.push_back(city_four);
	nodes_.push_back(city_one);
	nodes_.push_back(city_two);
	nodes_.push_back(city_three);
	nodes_.push_back(city_four);
	std::vector<City*> cities;
	cities.push_back(city_one);
	cities.push_back(city_two);
	objects_.push_back(new Road(cities));

	players_.push_back(new Player(this));
}

void Game::InitViews() {
	for (auto object: objects_) {
		views_.push_back(object->GetView());
	}
}

void Game::Draw() {
	for (auto view: views_) {
		view->Draw(painter_);
	}
}

void Game::ProcessKey(sf::Keyboard::Key key) {
	for (auto player : players_) {
		if (player->ProcessKey(key)) {
			break;
		}
	}
}

const std::vector<Node*>& Game::GetNodes() const {
	return nodes_;
}