#include "road.h"
#include "enum.h"
#include "city.h"
#include "../painter.h"
#include "../shapes.h"

Road::Road(std::vector<City*> cities)
{
    cities_connected_ = cities;
}

void Road::Tick() {
	throw 1;
}

bool Road::ProcessClick(int x, int y) {
	throw 1;
}

void Road::Draw(Painter* painter)
{
    Color road_color = {0, 255, 255};
    int x1 = cities_connected_[0]->x();
    int y1 = cities_connected_[0]->y();
    int x2 = cities_connected_[1]->x();
    int y2 = cities_connected_[1]->y();
    Line road_image = {x1, y1, x2, y2, road_color};
    painter->Draw(road_image);
}

int Road::GetCityPositionInVectors(int city_index)
{
	int position = -1; 
	for (int i = 0; i < 2; i++)
	{
		if (cities_indices_[i] == city_index)
		{
			position = i; 
		}
	}
	return position;
}


void Road::SetSylaInflux(int city_index, int syla_rate)
{
	int city_position = GetCityPositionInVectors(city_index);
	syla_influx_[city_position] = syla_rate;
}

void Road::TickBuild()
{
    for (int i = 0; i < 2; i++)
    {
        completeness_[i] += syla_influx_[i] / cost_; 
    }
    if (completeness_[0] + completeness_[1] > 1)
    {
        ResetTrade();
    }
}

void Road::ResetTrade()
{
    // By default, road state resets to trade after completion
    // with zero contingents on both sides
    state_ = TRADE;
    syla_influx_[0] = 0;
    syla_influx_[1] = 0;
}

void Road::TickMovePeace()
{
	// WTF is tick_time???
	double tick_time = 1;
	for (int i = 0; i < 2; i++)
	{
		int profit = trade_profit_ * contingents_[i][contingents_[i].size() - 1].GetThickness();
		
		cities_connected_[i]->AcquireSyla(profit);
		
		for (int j = 0; j < contingents_[i].size(); j++)
		{
			if ( !contingents_[i][j].MoveForward(tick_time, speed_, speed_, 1) )
				{
					contingents_[i].erase(contingents_[i].begin() + j);	
				}
		}
	}
}

void Road::TickMoveWar()
{
	// WTF is tick_time???
	double tick_time = 1;
	std::vector<Crew> front_crew;
	for (int i = 0; i < 2; i++)
	{
		front_crew.push_back(contingents_[i][contingents_[i].size() - 1]);
	}
	
	for (int i = 0; i < 2; i++)
	{
		double boundary_coordinate = (front_crew[i].GetEndPercentage() + 1 - front_crew[1-i].GetEndPercentage())/2;
		double advancement_speed = front_crew[i].OffensiveSpeed(front_crew[1-i], speed_);
		
		for (int j = 0; j < contingents_[i].size() - 1; j++)
		{
			if(!contingents_[i][j].MoveForward(tick_time, speed_, speed_, boundary_coordinate))
			{
				contingents_[i].erase(contingents_[i].begin() + j);
			}
		}
		if (!contingents_[i][contingents_[i].size() - 1].MoveForward(tick_time, speed_, advancement_speed, boundary_coordinate))
		{
			contingents_[i].erase(contingents_[i].begin() + contingents_[i].size() - 1);	
		}
	}
}