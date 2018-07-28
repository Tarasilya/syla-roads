#pragma once

class ObjectView;
class Game;

class GameObject
{
protected:
    ObjectView* view_;
    	
public:
    virtual void Tick() = 0;
	virtual ObjectView* GetView(Game* game) = 0;    
};
