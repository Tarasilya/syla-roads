#pragma once

#include <vector>
#include "node.h"
#include "../painter.h"

class Road;

class City : public Node
{
private:
    double x_;
    double y_;
    int city_index_;
    std::vector<Road*> roads_;
    double syla_reserve_;
    double syla_capacity_;
    double wall_;

public:
    City(double x_coord, double y_coord, int index);

    void SendCrew(double syla_rate, Road* target_road);
    void DamageWall(double syla_rate);
    void AcquireSyla(double syla);
    bool LoseSyla(double syla);

    void Tick(double tick_time);
    void Draw(Painter* painter);

    double x();
    double y();
    operator std::string() const;
};

