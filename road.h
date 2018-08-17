#ifndef __ROAD_H__
#define __ROAD_H__

#include "crew.h"
#include "enum.h"
#include "game_object.h"
#include "object_view.h"

#include <vector>
#include <deque>


class City;

class Road : public GameObject
{
private:
    std::vector<City*> cities_connected_;
    std::vector<int> cities_indices_;
    double speed_; // speed parameter indicating how fast the Crew is moving along the road.
    double cost_;  // speed parameter indicating how costly it is to complete a full road.
	double trade_profit_; // multiplicative factor that determines how much profit cities get from trading on this road
    std::vector<double> completeness_; // for the state when road is building/ upgraded, keeping track of the progress on both sides of it.
    std::vector<double> syla_influx_; // need these variables for one side of the road (for each city), store in a std::vector.
    std::vector<std::deque<Crew*>> contingents_;
    RoadState state_;

public:

    operator std::string() const;
    Road(std::vector<City*> cities);
    void Tick(double tick_time);

	void ResetWar();
	void ResetToTrade();
    double CityExpense(int city_index);

    int GetCityPositionInVectors(int city_index);
    void InitiateWar();
    void TickBuild(double tick_time);
	void TickTrade(double tick_time);
	void TickWar(double tick_time);
    void MoveContingents();
    void SetSylaInflux(int city_index, double syla_rate);
    void AddCrew(int position, double thickness);
    double CumulativeArmy(int position);

    RoadState GetState();
    const std::vector<City*>& GetCities();
    ObjectView* GetView(Game* game);
    double GetCompleteness(int index);
};


#endif // __ROAD_H__
