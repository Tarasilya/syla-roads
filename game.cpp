#include <iostream>
#include <cmath>
#include "game.h"
#include "painter.h"
#include "road.h"
#include "city.h"
#include "game_object.h"
#include "node.h"
#include "player.h"



Game::Game(Painter* painter) {
	painter_ = painter;
	InitMap();
	InitViews();
	players_.push_back(new Player((NodeView*) nodes_[0]->GetView(this)));
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
	Road* road = new Road(cities);
	objects_.push_back(road);

	city_one->AddRoad(road);
	city_two->AddRoad(road);

	total_time_ = 0;
	seconds_ = 0;
}

void Game::InitViews() {
	for (auto object: objects_) {
		views_.push_back(object->GetView(this));
	}
}

void Game::Draw() {
	for (auto view: views_) {
		view->Draw(painter_);
	}
}

void Game::ProcessKey(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::B)
	{

		((City*) objects_[0])->SendCrew(5, (Road*) objects_[2]);
	}
	else if (key == sf::Keyboard::C)
	{

		((City*) objects_[0])->SendCrew(0, (Road*) objects_[2]);
	}
	else if (key == sf::Keyboard::V)
	{
        ((Road*) objects_[2])->InitiateWar(0);
	}
	else if (key == sf::Keyboard::D)
	{
        ((City*) objects_[1])->SendCrew(6, (Road*) objects_[2]);
	}
	else {
		for (auto player : players_) {
			if (player->ProcessKey(key)) {
				break;
			}
		}
	}
}

void Game::Tick(double dt)
{
	bool vyvod = 0;
	total_time_ += dt;

	if (total_time_ > .05)
	{
        //std::cout << "vyvodin\n";
		vyvod = 1;
		total_time_ = 0;
	}

	for (auto object: objects_)
	{
		object->Tick(dt);
		if (vyvod)
		{
		//	std::cout <<(std::string) (*object);
		}
	}
}

const std::vector<Node*>& Game::GetNodes() const {
	return nodes_;
}
