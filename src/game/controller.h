#include <SFML/Graphics.hpp>

class Presenter;
class Map;
class Game;
class Painter;

class Controller {
private:
	Game* game_;
	sf::RenderWindow* window_;
	void ProcessKey(sf::Keyboard::Key key);
public:
	void Run();
};