#include "road.h"
#include "enum.h"
#include "city.h"
#include "crew.h"
#include "../painter.h"
#include "../shapes.h"
#include <cmath>
#include <sstream>
#include <iostream>

typedef std::string String;


Road::Road(std::vector<City*> cities)
{
    contingents_.assign(2, {});
    cities_indices_ = {0, 1};
    cities_connected_ = cities;
    state_ = CONSTRUCTION;
    syla_influx_.assign(2, 0);
    completeness_.assign(2, 0);
    speed_ = 10;
    cost_ = 0.1;
    trade_profit_ = 1;
}

Road::operator std::string() const
{
    std::stringstream ss;
    ss << "Cities' indices: " << cities_indices_[0] << " " << cities_indices_[1] <<
    "\ncompleteness: " << completeness_[0] << " " << completeness_[1] << "\n";
    return ss.str();
}

void Road::Tick(double tick_time) {
    if (state_ == CONSTRUCTION)
    {
        TickBuild(tick_time);
    }
    else if (state_  == TRADE)
    {
        TickTrade(tick_time);
    }
    else if (state_ == WAR)
    {
        TickWar(tick_time);
    }

}


double Road::CityExpense(int city_index)
{
    double expense;
    int position_ind = GetCityPositionInVectors(city_index);
    int num_crew = contingents_[position_ind].size();
    if (num_crew > 0)
    {
        expense = contingents_[position_ind][0]->GetThickness();
    }
    else
    {
        expense = 0;
    }
    return expense;
}


void Road::Draw(Painter* painter)
{
    Color road_color = {0, 255, 255};
    double x1 = cities_connected_[0]->x();
    double y1 = cities_connected_[0]->y();
    double x2 = cities_connected_[1]->x();
    double y2 = cities_connected_[1]->y();
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


void Road::SetSylaInflux(int city_index, double syla_rate)
{
	int city_position = GetCityPositionInVectors(city_index);
    std::cout << "SetSylaInflux: city_pos " << city_position << " syla " << syla_rate << "\n";
	syla_influx_[city_position] = syla_rate;
	if (state_ != CONSTRUCTION)
	{
        AddCrew(city_position, syla_rate);
    }
}

void Road::AddCrew(int position, double thickness)
{
    Crew* new_crew = new Crew(thickness);
    contingents_[position].push_front(new_crew);
}

void Road::TickBuild(double tick_time)
{
    for (int i = 0; i < 2; i++)
    {
        double syla_spending = tick_time * syla_influx_[i];
        if (cities_connected_[i]->LoseSyla(syla_spending))
        {
            completeness_[i] += tick_time * syla_influx_[i] / cost_;
        }
    }
    if (completeness_[0] + completeness_[1] > 1)
    {
        ResetToTrade();
    }
}

void Road::ResetToTrade()
{
    // By default, road state resets to trade after completion
    // with zero contingents on both sides
    state_ = TRADE;
    syla_influx_[0] = 0;
    syla_influx_[1] = 0;


}

void Road::InitiateWar(int city_index)
{
    state_ = WAR;
    syla_influx_[0] = 0;
    syla_influx_[1] = 0;
    contingents_.assign(2, {});
    std::cerr << contingents_[0].size();
}

void Road::TickTrade(double tick_time)
{
	for (int i = 0; i < 2; i++)
	{
        if  (contingents_[i].size())
        {
            if (contingents_[i].back()->GetEndPercentage() >= 1)
            {
                double profit = tick_time*trade_profit_ * contingents_[i].back()->GetThickness();
                cities_connected_[i]->AcquireSyla(profit);
            }
            if (contingents_[i].front()->GetStartPercentage() <= 0)
            {
                double maintenance_cost = contingents_[i].front()->GetThickness()*tick_time;
                if (!cities_connected_[i]->LoseSyla(maintenance_cost))
                {
                    AddCrew(i, 0);
                }
            }
            for (int j = 0; j < (int) contingents_[i].size(); j++)
            {
                if ( !contingents_[i][j]->MoveForward(tick_time, speed_, speed_, 1, j) )
                    {
                        contingents_[i].erase(contingents_[i].begin() + j);
                    }
            }
        }
	}
}

void Road::TickWar(double tick_time)
{


	std::vector<Crew*> front_crew;

	for (int i = 0; i < 2; i++)
	{
        if (contingents_[i].size())
        {
            front_crew.push_back(contingents_[i][contingents_[i].size() - 1]);
        }
        else
        {
            front_crew.push_back(new Crew(syla_influx_[i]));
        }
	}


	for (int i = 0; i < 2; i++)
	{
        if (contingents_[i].size())
        {
            double boundary_coordinate = (front_crew[i]->GetEndPercentage() + 1 - front_crew[1-i]->GetEndPercentage())/2;
            double advancement_speed = front_crew[i]->OffensiveSpeed(front_crew[1-i], speed_);

            if (!cities_connected_[i]->LoseSyla(contingents_[i].front()->GetThickness()*tick_time))
            {
                AddCrew(i, 0);
            }
            for (int j = 0; j < (int) contingents_[i].size() - 1; j++)
            {
                if(!contingents_[i][j]->MoveForward(tick_time, speed_, speed_, boundary_coordinate, j))
                {
                    contingents_[i].erase(contingents_[i].begin() + j);
                }
            }
            if (!contingents_[i].back()->MoveForward(tick_time, speed_, advancement_speed, boundary_coordinate, (int) contingents_[i].size() - 1 ))
            {
                contingents_[i].pop_back();
            }
            if (front_crew[i]->GetEndPercentage() >= 1)
            {
                cities_connected_[!i]->DamageWall(tick_time*(front_crew[i]->GetThickness() - front_crew[1-i]->GetThickness() ));
            }
        }
	}
}
