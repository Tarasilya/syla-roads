#pragma once

class ObjectView;
class Game;

class GameObject
{
public:
    virtual void Tick() = 0;
	virtual ObjectView* GetView(Game* game) = 0;    
};
