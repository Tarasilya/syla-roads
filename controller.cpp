#include "controller.h"
#include "painter.h"
#include "game.h"
#include "shapes.h"
#include "presenter.h"
#include "map.h"
#include "map_choice_presenter.h"

void Controller::Run() {
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(600, 600), "SYLA", sf::Style::Fullscreen);
	painter_ = new Painter(window);
	game_ = new Game(painter_);

	int side = 100;

	while (window->isOpen()) {
	    sf::Event event;
	    while (window->pollEvent(event))
	    {
	        if (event.type == sf::Event::Closed) {
	            window->close();
	            break;
	        }

	        if (event.type == sf::Event::KeyPressed) {
	        	if (event.key.code == sf::Keyboard::Escape) {
		            window->close();
		            break;
		        }
		        else {
		        	ProcessKey(event.key.code);
                }
	        }

	    }
		window->clear();
		game_->Draw();
		if (current_presenter_) {
			current_presenter_->Draw();
		}
		window->display();
	}
}

void Controller::StartNewGame(Map map) {
	delete game_;
	game_ = new Game(painter_, map);
}

bool Controller::ProcessKey(sf::Keyboard::Key key) {
	if (key == MAP_CHOICE_KEY) {
		game_->Pause();
		current_presenter_ = new MapChoicePresenter(this, painter_);
		return true;
	}

	return false;
}
