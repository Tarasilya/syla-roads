#pragma once

#include "../painter.h"

class GameObject
{
public:
    virtual void Tick() = 0;
    virtual void Draw(Painter* painter) = 0;
    virtual bool ProcessClick(int x_scr, int y_scr) = 0;
};
