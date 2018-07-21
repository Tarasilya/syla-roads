#include <iostream>
#include <cmath>
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
	City* city_one = new City(200, 100, 0);
	City* city_two = new City(400, 300, 1);
	objects_.push_back(city_one);
	objects_.push_back(city_two);
	std::vector<City*> cities;
	cities.push_back(city_one);
	cities.push_back(city_two);
	objects_.push_back(new Road(cities));
	total_time_ = 0;
	seconds_ = 0;
}

void Game::Redraw() {
	for (auto object: objects_) {
		object->Draw(painter_);
	}
}

void Game::ProcessKey(sf::Keyboard::Key key)
{
	if (key == sf::Keyboard::B)
	{

		((City*) objects_[0])->SendCrew(5, (Road*) objects_[2]);
	}
	if (key == sf::Keyboard::C)
	{

		((City*) objects_[0])->SendCrew(0, (Road*) objects_[2]);
	}
	if (key == sf::Keyboard::V)
	{
        ((Road*) objects_[2])->InitiateWar(0);
	}
	if (key == sf::Keyboard::D)
	{
        ((City*) objects_[1])->SendCrew(6, (Road*) objects_[2]);
	}
}

void Game::Tick(double dt)
{
	bool vyvod = 0;
	total_time_ += dt;

	if (total_time_ > .05)
	{
        std::cout << "vyvodin\n";
		vyvod = 1;
		total_time_ = 0;
	}

	for (auto object: objects_)
	{
		object->Tick(dt);
		if (vyvod)
		{
			std::cout <<(std::string) (*object);
		}
	}
}
