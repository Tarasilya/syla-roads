#include "painter.h"
#include "game.h"

int main() {
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(600, 600), "SYLA", sf::Style::Fullscreen);
	Painter* painter = new Painter(window);
	Game* game = new Game(painter);
	t = clock();
	while (window->isOpen()) {

	    sf::Event event;
	    while (window->pollEvent(event))
	    {
	        if (event.type == sf::Event::Closed) {
	            window->close();
	            break;
	        }

	        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
	            window->close();
	            break;
	        }
	    }	
	    int dt = clock() - t;
	    int t = clock();	
	    game->Tick(dt * 1.0 / CLOCKS_PER_SEC);
		window->clear();
		game->Redraw();
		window->display();
	}

}