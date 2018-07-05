#ifndef __ROAD_H__
#define __ROAD_H__

#include "city.h"
#include "crew.h"
#include "enum.h"

class Road
{
private:
    vector<int> cities_indices_;
    vector<City*> cities_connected_;
    double speed_; // speed parameter indicating how fast the Crew is moving along the road.
    double cost_;  // speed parameter indicating how costly it is to complete a full road.

    vector<double> completeness; // for the state when road is building/ upgraded, keeping track of the progress on both sides of it.
    vector<double> syla_influx_; // need these variables for one side of the road (for each city), store in a vector.
    vector<vector<Crew>> contingents_;
    RoadState state_;

public:
    void Tick();
    void Draw();
    bool ProcessClick(double x_scr, double y_scr);

    int GetCityPositionInVectors(int city_index);
    void BuildRoad(int city_index, double syla);
    void MoveContingents();
};


#endif // __ROAD_H__
