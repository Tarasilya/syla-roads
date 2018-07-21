#pragma once

#include "painter.h"

class GameObject;
class ObjectView;
class Node;
class Player;

class Game {
private:
	Painter* painter_;
	std::vector<GameObject*> objects_;
	std::vector<Node*> nodes_;
	std::vector<ObjectView*> views_;
	std::vector<Player*> players_;

	void InitMap();
	void InitViews();
	
public: 
	Game(Painter* painter);
	void Run();
	void Draw();
	void ProcessKey(sf::Keyboard::Key key);
	const std::vector<Node*>& GetNodes() const;
};