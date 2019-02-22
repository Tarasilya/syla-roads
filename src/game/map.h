#pragma once

#include <fstream>
#include <vector>

class GameObject;
class City;

class Map {
private:
	std::vector<GameObject*> objects_;
	std::vector<City*> cities_;
	std::string filename_;
	Map();
	void ReadObjects();
	void ReadObject(std::ifstream& in);

public:
	Map(std::string filename);
	const std::vector<GameObject*>& GetObjects();
	const std::vector<City*>& GetCities();
};