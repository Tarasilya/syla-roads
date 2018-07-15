#pragma once
#include "game/game_object.h"
#include "map.h"
#include <fstream>

class Map {
private:
	std::vector<GameObject*> objects_;
	std::string filename_;

	Map();
	void ReadObjects();
	GameObject* ReadObject(std::ifstream& in);
public:
	Map(std::string& filename);
	const std::vector<GameObject*>& GetObjects();
	static Map DefaultMap();
};