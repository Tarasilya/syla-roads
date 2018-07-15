#pragma once

#include "../painter.h"

class GameObject
{
public:
    virtual void Tick() = 0;
    virtual void Draw(Painter* painter) = 0;
    virtual bool ProcessClick(double x_scr, double y_scr) = 0;
};
