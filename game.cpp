#include "game.h"
#include "painter.h"
#include "map.h"
#include "game/road.h"
#include "game/city.h"
#include "game/game_object.h"

Game::Game(Painter* painter) {
	Game(painter, Map::DefaultMap());
}

Game::Game(Painter* painter, Map map) {
	painter_ = painter;
	objects_ = map.GetObjects();
}


void Game::Draw() {
	for (auto object: objects_) {
		object->Draw(painter_);
	}
}

void Game::ProcessKey(sf::Keyboard::Key key) {

}

void Game::Pause() {

}