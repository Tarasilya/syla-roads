#pragma once

#include <SFML/Window.hpp>
#include <vector>

class GameObject;
class ObjectView;
class Node;
class Player;
class Painter;
class Map;
class GameConfig;

class Game {
private:
	Painter* painter_;
	Map* map_;
	double total_time_;
	int seconds_;

	std::vector<ObjectView*> views_;
	std::vector<Player*> players_;

	void InitMap();
	void InitViews();
	
public: 
	Game(Painter* painter, GameConfig* config);
	void Run();
	void Draw();
	void ProcessKey(sf::Keyboard::Key key);
	void Tick(double dt);
	const std::vector<Node*>& GetNodes() const;
	std::vector<int> GetScores();
};
