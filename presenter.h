#pragma once

class Controller;
class Presenter;
class Painter;

#include <SFML/Window.hpp>

class Presenter {
protected:
	Controller* controller_;
	Painter* painter_;
public:
	Presenter(Controller* controller, Painter* painter);
	virtual void Draw() = 0;
	virtual void ProcessKey(sf::Keyboard::Key key) = 0;
};