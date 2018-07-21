#pragma once

#include "../painter.h"

class GameObject
{

public:
    virtual operator std::string() const = 0;
    virtual void Tick(double tick_time) = 0;
    virtual void Draw(Painter* painter) = 0;
 };
