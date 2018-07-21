#include "painter.h"
#include "game.h"
#include <iostream>

int main() {
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(300, 300), "SYLA");
	Painter* painter = new Painter(window);
	Game* game = new Game(painter);

    std::cout << CLOCKS_PER_SEC << "\n";
	clock_t t = clock();

	while (window->isOpen()) {

	    sf::Event event;
	    while (window->pollEvent(event))
	    {
	        if (event.type == sf::Event::Closed) {
	            window->close();
	            break;
	        }

	        if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window->close();
                    break;
                }
                else
                {
                    game->ProcessKey(event.key.code);
                }
	        }
	    }
	    clock_t dt = clock() - t;
	    t = clock();
	    game->Tick(dt * 1.0 / CLOCKS_PER_SEC);
		window->clear();
		game->Redraw();
		window->display();
	}

}
