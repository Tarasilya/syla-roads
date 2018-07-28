#ifndef __CREW_H__
#define __CREW_H__

#include <algorithm>
#include "enum.h"

class Crew
{
private:
    double thickness_; // kon
    double start_percentage_;
    double end_percentage_;
    int position; // kon
    Fraction entity_;
public:
    Crew(double thickness);
    bool MoveForward(double tick_time, double start_speed, double end_speed, double boundary_coordinate, int crew_index);
    //output indicates if the Crew is still present on the board
    double OffensiveSpeed(Crew* enemy_crew, double road_speed);
    //output indicates the speed of movement as a result of
    //engagement
    double GetThickness();
    double GetStartPercentage();
	double GetEndPercentage();

};

#endif // __CREW_H__
