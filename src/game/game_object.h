#pragma once

#include <string>

class ObjectView;
class Game;

class GameObject
{
protected:
    ObjectView* view_;

public:
    virtual void Tick(double tick_time) = 0;
   	virtual ObjectView* GetView(Game* game) = 0;    
};
