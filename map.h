#pragma once

#include <fstream>
#include <vector>

class GameObject;
class Node;

class Map {
private:
	std::vector<GameObject*> objects_;
	std::vector<Node*> nodes_;

	std::string filename_;

	Map();
	void ReadObjects();
	void ReadObject(std::ifstream& in);
public:
	Map(std::string filename);
	const std::vector<GameObject*>& GetObjects();
	const std::vector<Node*>& GetNodes();
	static Map* DefaultMap();
};