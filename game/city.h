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
    double syla_;
    double capacity_;
    double wall_;

public:
    City(int x_coord, int y_coord, int index);

    void SendCrew(double syla_rate, Road* target_road);
    void DamageWall(double syla_rate);
    void AcquireSyla(double syla);
    double CalculateSylaOutflux();

    void Tick();
    void Draw(Painter* painter);
    bool ProcessClick(int x_scr, int y_scr);

    int x();
    int y();
};

