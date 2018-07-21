#ifndef __ROAD_H__
#define __ROAD_H__

#include "crew.h"
#include "enum.h"
#include "game_object.h"
#include "../object_view.h"

#include <vector>

class City;

class Road : public GameObject
{
private:
    ObjectView* view_;
    std::vector<int> cities_indices_;
    std::vector<City*> cities_connected_;
    double speed_; // speed parameter indicating how fast the Crew is moving along the road.
    double cost_;  // speed parameter indicating how costly it is to complete a full road.

    std::vector<double> completeness; // for the state when road is building/ upgraded, keeping track of the progress on both sides of it.
    std::vector<double> syla_influx_; // need these variables for one side of the road (for each city), store in a std::vector.
    std::vector<std::vector<Crew>> contingents_;
    RoadState state_;

public:
    Road(std::vector<City*> cities);
    void Tick();

    int GetCityPositionInVectors(int city_index);
    void BuildRoad(int city_index, double syla);
    void MoveContingents();

    const std::vector<City*>& GetCities();
    ObjectView* GetView();
};


#endif // __ROAD_H__
