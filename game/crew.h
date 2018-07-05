#ifndef __CREW_H__
#define __CREW_H__

#include "enum.h"
class Crew
{
private:
    int thickness_; // kon
    double start_percentage_;
    double end_percentage_;
    int position; // kon
    Fraction entity_;
public:
    bool MoveForward(double tick_time, double speed);
    //output indicates if the Crew is still present on the board
    double Engage(Crew enemy_crew);
    //output indicates the speed of movement as a result of
    //engagement
    double GetThickness();

};

#endif // __CREW_H__
