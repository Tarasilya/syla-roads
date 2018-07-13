#pragma once

#include <vector>
#include "node.h"
#include "../painter.h"

class Road;

class City : public Node
{
private:
    int x_;
    int y_;
    int city_index_;
    std::vector<Road*> roads_;
    int syla_reserve_;
    int syla_capacity_;
    int wall_;

public:
    City(int x_coord, int y_coord, int index);

    void SendCrew(int syla_rate, Road* target_road);
    void DamageWall(int syla_rate);
    void AcquireSyla(int syla);
    int CalculateSylaOutflux();

    void Tick();
    void Draw(Painter* painter);
    //bool ProcessClick(int x_scr, int y_scr);

    int x();
    int y();
};

