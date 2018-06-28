#ifndef __CITY_H__
#define __CITY_H__

#include "Road.h"

class City : public Node
{
private:
    int city_index_;
    vector<Road*> roads_;
    double syla_, capacity_, wall_;
    City(int x, int y);

public:
    void SendCrew(double syla_rate, Road* target_road);
    void DamageWall(double syla_rate);
    void AcquireSyla(double syla);
    void Tick();
    double CalculateSylaOutflux();
};

#endif
