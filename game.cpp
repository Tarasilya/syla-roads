#include "game.h"
#include "painter.h"

Game::Game(Painter* painter) {
	painter_ = painter;

}

void Game::redraw() {
	painter_->draw({100, 100, 300, 300});
}