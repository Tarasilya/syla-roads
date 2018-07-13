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

int GetCityPositionInVectors(int city_index)
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
