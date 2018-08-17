#ifndef __NODE_H__
#define __NODE_H__

#include "enum.h"
#include "game_object.h"
#include "player.h"

class Node : public GameObject
{
protected:
    Player* owner_;
    double x_;
    double y_;

public:
    Player* GetOwner();

    double x();
    double y();
    virtual double GetSyla();
};


#endif // __NODE_H__
