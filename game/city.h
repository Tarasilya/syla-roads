#pragma once

#include <vector>
#include "node.h"
#include "../object_view.h"

class Road;

class City : public Node
{
private:
    int index_;
    std::vector<Road*> roads_;
    double syla_;
    double capacity_;
    double wall_;

public:
    City(double x_coord, double y_coord, int index);

    void SendCrew(double syla_rate, Road* target_road);
    void DamageWall(double syla_rate);
    void AcquireSyla(double syla);
    double CalculateSylaOutflux();

    void Tick();
    
    int GetIndex();
    ObjectView* GetView(Game* game);
    const std::vector<Road*>& GetRoads();
};

