#pragma once

class ObjectView;

class GameObject
{
public:
    virtual void Tick() = 0;
	virtual ObjectView* GetView() = 0;    
};
