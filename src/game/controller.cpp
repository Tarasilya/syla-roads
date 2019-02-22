#include "controller.h"
#include "game.h"
#include "game_config.h"

#include "painter/painter.h"

#include <iostream>

void Controller::Run() {
	window_ = new sf::RenderWindow(sf::VideoMode(1000, 1000), "SYLA");
	Painter* painter = new Painter(window_);
	GameConfig& config = GameConfig::getInstance();
	game_ = new Game(painter, config);

	double t = clock();
	while (window_->isOpen()) {
	    sf::Event event;
	    while (window_->pollEvent(event))
	    {
	        if (event.type == sf::Event::Closed) {
	            window_->close();
	            break;
	        }

	        if (event.type == sf::Event::KeyPressed) {
                ProcessKey(event.key.code);
	        }
	    }
	    clock_t dt = clock() - t;
	    t = clock();
	    game_->Tick(dt * 1.0 / CLOCKS_PER_SEC);
		window_->clear({76, 180, 115});
		game_->Draw();
		window_->display();
	}
}

void Controller::ProcessKey(sf::Keyboard::Key key) {
	if (key == sf::Keyboard::Escape) {
        window_->close();
        exit(0);
    }
    else {
    	game_->ProcessKey(key);
    }
}
