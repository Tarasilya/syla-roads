#pragma once

#include "enum.h"
#include "game_object.h"
#include "player.h"
#include "object_view.h"

#include <vector>

class Player;
class Road;

class City : public GameObject
{
private:
    Player* owner_;
    double x_;
    double y_;    
    int player_id_;
    int index_;
    std::vector<Road*> roads_;
    double syla_reserve_;
    double syla_capacity_;
    double wall_;
    double texas_tax_collection_rate_;

public:
    City(double x_coord, double y_coord, int index, int player_id);

    void SendCrew(double syla_rate, Road* target_road);
    void DamageWall(double syla_rate);
    void AcquireSyla(double syla);
    bool LoseSyla(double syla);

    void Tick(double tick_time) override;

    void AddRoad(Road* road);
    void ChangeOwner(Player* new_owner);
    void ResetCapture();

    Player* GetOwner();
    double x();
    double y();
    double GetSyla();
    int GetIndex();
    double GetWall();
    ObjectView* GetView(Game* game) override;
    const std::vector<Road*>& GetRoads();
    int GetPlayerId();
};

