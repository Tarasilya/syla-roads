#ifndef __NODE_H__
#define __NODE_H__

#include "enum.h"
#include "game_object.h"

class Node : public GameObject
{
private:
    Fraction entity_;

public:
    Fraction GetFraction();
    virtual void Tick() = 0;
    virtual void Draw() = 0;
    virtual bool ProcessClick(double x_scr, double y_scr) = 0;
};


#endif // __NODE_H__
