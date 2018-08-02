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
	nodes_.push_back(new City(-0.75, 0, 0));
	nodes_.push_back(new City(-0.25, 0, 1));
	nodes_.push_back(new City(0.25, 0, 2));
	nodes_.push_back(new City(0.75, 0, 3));
	nodes_.push_back(new City(0, -0.5, 4));
	nodes_.push_back(new City(0, 0.5, 5));
	for (auto node: nodes_) {
		objects_.push_back(node);
	}
	objects_.push_back(new Road({(City*) nodes_[0], (City*) nodes_[1]}));
	objects_.push_back(new Road({(City*) nodes_[1], (City*) nodes_[4]}));
	objects_.push_back(new Road({(City*) nodes_[1], (City*) nodes_[2]}));
	objects_.push_back(new Road({(City*) nodes_[1], (City*) nodes_[5]}));
	objects_.push_back(new Road({(City*) nodes_[4], (City*) nodes_[2]}));
	objects_.push_back(new Road({(City*) nodes_[3], (City*) nodes_[5]}));

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
