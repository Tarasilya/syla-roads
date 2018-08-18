#pragma once

#include <vector>
#include "node.h"
#include "object_view.h"

class Player;
class Road;

class City : public Node
{
private:
    int player_id_;
    int index_;
    std::vector<Road*> roads_;
    double syla_reserve_;
    double syla_capacity_;
    double wall_;

public:
    City(double x_coord, double y_coord, int index, int player_id);

    void SendCrew(double syla_rate, Road* target_road);
    void DamageWall(double syla_rate);
    void AcquireSyla(double syla);
    bool LoseSyla(double syla);

    virtual void Tick(double tick_time) override;

    void AddRoad(Road* road);
    void ChangeOwner(Player* new_owner);
    void ResetCapture();

    virtual double GetSyla() override;
    int GetIndex();
    double GetWall();
    virtual ObjectView* GetView(Game* game) override;
    const std::vector<Road*>& GetRoads();
    int GetPlayerId();
};

