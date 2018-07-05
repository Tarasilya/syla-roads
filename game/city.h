#ifndef __CITY_H__
#define __CITY_H__

#include "road.h"

class City : public Node
{
private:
    int x;
    int y;
    int city_index_;
    vector<Road*> roads_;
    double syla_;
    double capacity_;
    double wall_;

public:
    City(int x_coord, int y_coord, int index)
    {
        x = x_coord;
        y = y_coord;
        city_index_ = index;
        syla_ = 0;
        capacity_ = 100;
        wall_ = 100;
    }

    void SendCrew(double syla_rate, Road* target_road);
    void DamageWall(double syla_rate);
    void AcquireSyla(double syla);
    double CalculateSylaOutflux();

    void Tick();
    void Draw();
    bool ProcessClick(double x_scr, double y_scr);
};

#endif
