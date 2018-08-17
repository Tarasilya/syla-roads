#include "map.h"
#include "city.h"
#include "road.h"
#include "game_object.h"
#include "node.h"

#include <vector>
#include <fstream>
#include <string>
#include <iostream>

Map::Map() {
}

Map* Map::DefaultMap() {
	Map* map = new Map();
	map->nodes_.push_back(new City(-0.75, 0, 0));
	map->nodes_.push_back(new City(-0.25, 0, 1));
	map->nodes_.push_back(new City(0.25, 0, 2));
	map->nodes_.push_back(new City(0.75, 0, 3));
	map->nodes_.push_back(new City(0, -0.5, 4));
	map->nodes_.push_back(new City(0, 0.5, 5));
	for (auto node: map->nodes_) {
		map->objects_.push_back(node);
	}
	map->objects_.push_back(new Road({(City*) map->nodes_[0], (City*) map->nodes_[1]}));
	map->objects_.push_back(new Road({(City*) map->nodes_[1], (City*) map->nodes_[4]}));
	map->objects_.push_back(new Road({(City*) map->nodes_[1], (City*) map->nodes_[2]}));
	map->objects_.push_back(new Road({(City*) map->nodes_[1], (City*) map->nodes_[5]}));
	map->objects_.push_back(new Road({(City*) map->nodes_[4], (City*) map->nodes_[2]}));
	map->objects_.push_back(new Road({(City*) map->nodes_[3], (City*) map->nodes_[5]}));

	return map;
}

const std::vector<GameObject*>& Map::GetObjects() {
	return objects_;
}

const std::vector<Node*>& Map::GetNodes() {
	return nodes_;
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
		in >> x >> y;
		std::cerr << "read city " << x << " " << y << std::endl;
		City* city = new City(x, y, objects_.size());
		nodes_.push_back(city);
		objects_.push_back(city);
	}
	else {
		int city1, city2;
		in >> city1 >> city2;
		std::cerr << "read road " << city1 << " " << city2 << std::endl;
		objects_.push_back(new Road({(City*) objects_[city1], (City*) objects_[city2]}));
	}
}