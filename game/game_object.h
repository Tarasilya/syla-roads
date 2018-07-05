#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

class GameObject
{
public:
    virtual void Tick() = 0;
    virtual void Draw() = 0;
    virtual bool ProcessClick(double x_scr, double y_scr) = 0;
};
#endif // __GAMEOBJECT_H__
