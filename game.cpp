#include <iostream>
#include <cmath>
#include "game.h"
#include "painter.h"
#include "road.h"
#include "city.h"
#include "game_object.h"
#include "node.h"
#include "player.h"
#include "map.h"
#include "game_config.h"

Game::Game(Painter* painter, GameConfig* config) {
	painter_ = painter;
	InitMap();
	InitViews();
	for (int i = 0; i < 2; i++) {
		players_.push_back(new Player(config->GetControls(i), (NodeView*) GetNodes()[0]->GetView(this)));
	}
	for (auto node: map_->GetNodes()) {
		City* city = (City*) node;
		city->player_ = players_[0];
	}
}

void Game::InitMap() {
	map_ = new Map("def.map");

	total_time_ = 0;
	seconds_ = 0;
}

void Game::InitViews() {
	for (auto object: map_->GetObjects()) {
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
	for (auto player : players_) {
		if (player->ProcessKey(key)) {
			break;
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

	for (auto object: map_->GetObjects())
	{
		object->Tick(dt);
		if (vyvod)
		{
		//	std::cout <<(std::string) (*object);
		}
	}
}

const std::vector<Node*>& Game::GetNodes() const {
	return map_->GetNodes();
}
