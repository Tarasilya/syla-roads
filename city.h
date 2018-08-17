#pragma once

#include <vector>
#include "node.h"
#include "object_view.h"

class Player;
class Road;

class City : public Node
{
private:
    int index_;
    std::vector<Road*> roads_;
    double syla_reserve_;
    double syla_capacity_;
    double wall_;

public:
    Player* player_;
    City(double x_coord, double y_coord, int index);

    void SendCrew(double syla_rate, Road* target_road);
    void DamageWall(double syla_rate);
    void AcquireSyla(double syla);
    bool LoseSyla(double syla);

    void Tick(double tick_time);

    void AddRoad(Road* road);
    void ChangeOwner(Player* new_owner);

    operator std::string() const;
    int GetIndex();
    double GetWall();
    Player* GetOwner();
    ObjectView* GetView(Game* game);
    const std::vector<Road*>& GetRoads();
};

