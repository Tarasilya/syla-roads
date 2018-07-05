#ifndef __CITY_H__
#define __CITY_H__

#include <vector>

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
    void Draw();
    bool ProcessClick(double x_scr, double y_scr);
};

#endif
