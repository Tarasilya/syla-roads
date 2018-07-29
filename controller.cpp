#include "controller.h"
#include "painter.h"
#include "game.h"
#include <iostream>

void Controller::Run() {
	window_ = new sf::RenderWindow(sf::VideoMode(1000, 1000), "SYLA");
	Painter* painter = new Painter(window_);
	game_ = new Game(painter);

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
		window_->clear();
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
