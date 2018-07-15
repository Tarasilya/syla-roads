#include <SFML/Window.hpp>

class Presenter;
class Map;
class Game;
class Painter;

const int MAP_CHOICE_KEY = sf::Keyboard::M;

class Controller {
private:
	Game* game_;
	Painter* painter_;
	Presenter* current_presenter_;
	bool ProcessKey(sf::Keyboard::Key key);
public:
	void Run();
	void StartNewGame(Map map);
};