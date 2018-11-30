#include "map.h"
#include "city.h"
#include "road.h"
#include "game_object.h"

#include <vector>
#include <fstream>
#include <string>
#include <iostream>

Map::Map() {
}


const std::vector<GameObject*>& Map::GetObjects() {
	return objects_;
}

const std::vector<City*>& Map::GetCities() {
	return cities_;
}

Map::Map(std::string filename) {
	filename_ = filename;
	ReadObjects();
}

void Map::ReadObjects() {
	int count;
	std::ifstream in (filename_);

	in >> count;

	for (int i = 0; i < count; i++) {
		ReadObject(in);
	}
}

void Map::ReadObject(std::ifstream& in) {
	int type;
	in >> type;
	if (type == 0) {
		double x, y;
		int player_id;
		in >> x >> y >> player_id;
		std::cerr << "read city " << x << " " << y << std::endl;
		City* city = new City(x, y, objects_.size(), player_id);
		cities_.push_back(city);
		objects_.push_back(city);
	}
	else {
		int city1, city2;
		in >> city1 >> city2;
		std::cerr << "read road " << city1 << " " << city2 << std::endl;
		objects_.push_back(new Road({(City*) objects_[city1], (City*) objects_[city2]}));
	}
}