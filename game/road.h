#ifndef __ROAD_H__
#define __ROAD_H__

#include "City.h"
#include "Crew.h"
#include "Enum.h"

class Road
{
private:
    vector<int> cities_indices_;
    vector<City> cities_connected_;
    double permittivity_, prefix_, suffix_;
    vector<double> syla_influx_ // need these variables for each side of the road (for each city), store in a vectore
    vector<vector<Crew>> contingents_
    RoadState state_;

public:
    void Tick();
    int GetCityPositionInVectors(int city_index_);

};


#endif // __ROAD_H__
