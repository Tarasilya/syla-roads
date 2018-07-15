#include "map.h"
#include "game/city.h"
#include "game/road.h"

#include <vector>
#include <fstream>
#include <string>
#include <iostream>

Map::Map() {}

Map Map::DefaultMap() {
	Map map;
	City* city_one = new City(200, 100, 0);
	City* city_two = new City(400, 300, 1);
	map.objects_.push_back(city_one);
	map.objects_.push_back(city_two);
	std::vector<City*> cities;
	cities.push_back(city_one);
	cities.push_back(city_two);
	map.objects_.push_back(new Road(cities));
	return map;
}

const std::vector<GameObject*>& Map::GetObjects() {
	if (objects_.size() == 0) {
		ReadObjects();
	}
	return objects_;
}

Map::Map(std::string& filename) {
	std::cerr << "constructing map from " << filename << std::endl;
	filename_ = filename;
}

void Map::ReadObjects() {
	int count;
	std::ifstream in (filename_);

	in >> count;

	for (int i = 0; i < count; i++) {
		objects_.push_back(ReadObject(in));
		std::cerr << "line " << i << std::endl;
	}
	std::cerr << "ReadObjects finished" << std::endl;
}

GameObject* Map::ReadObject(std::ifstream& in) {
	int type;
	in >> type;
	if (type == 0) {
		double x, y;
		in >> x >> y;
		std::cerr << "read city " << x << " " << y << std::endl;
		City* city = new City(x, y, objects_.size());
		return city;
	}
	else {
		int city1, city2;
		in >> city1 >> city2;
		std::cerr << "read road " << city1 << " " << city2 << std::endl;
		std::vector<City*> cities;
		std::cerr << "1" << std::endl;
		cities.push_back((City*) objects_[city1]);
		std::cerr << "2" << std::endl;
		cities.push_back((City*) objects_[city2]);
		std::cerr << "3" << std::endl;
		return new Road(cities);
	}
}