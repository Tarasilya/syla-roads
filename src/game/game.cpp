#include "game.h"
#include "road.h"
#include "city.h"
#include "game_object.h"
#include "player.h"
#include "map.h"
#include "game_config.h"

#include "painter/painter.h"

#include <iostream>
#include <cmath>
#include <sstream>

Game::Game(Painter* painter, GameConfig& config) {
	painter_ = painter;
	InitMap();
	InitViews();
	for (int i = 0; i < 2; i++) {
		players_.push_back(new Player(config.GetControls(i), (CityView*) GetCities()[0]->GetView(this), i));
	}
	for (auto city: map_->GetCities()) {
		int pid = city->GetPlayerId();
		if (pid != -1) {
			city->ChangeOwner(players_[pid]);
		}
	}
}

void Game::InitMap() {
	map_ = new Map("maps/SMALL.map");

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
	std::vector<double> scores = GetScores();
	for (int i = 0; i < 2; i++)
	{
		std::stringstream ss;
		ss << scores[i];
		Text score = { 0.5 - 1 * i, 0.8, ss.str()};
		painter_->Draw(score);
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

std::vector<double> Game::GetScores()
{
	std::vector<double> scores(2, 0);
	for (auto city: GetCities())
	{
		for (int i = 0; i < 2; i++)
		{
			if (city->GetOwner() == players_[i])
			{
				scores[i] += city->GetSyla();
			}
		}
	}
	return scores;
}

const std::vector<City*>& Game::GetCities() const {
	return map_->GetCities();
}
