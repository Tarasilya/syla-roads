#pragma once

#include "enum.h"
#include "player.h"

#include <algorithm>

class Crew
{
private:
    double thickness_; // kon
    double start_percentage_;
    double end_percentage_;
    Player* entity_;
public:
    Crew(double thickness);
    // output indicates if the Crew is still present on the board
    bool MoveForward(double tick_time, double start_speed, double end_speed, double boundary_coordinate, int crew_index);
    /* 
     output indicates the speed of movement as a result of
     engagement
    */
    double OffensiveSpeed(Crew* enemy_crew, double road_speed);
    double GetThickness();
    double GetStartPercentage();
	double GetEndPercentage();
    double GetCumulativeSyla();

};
