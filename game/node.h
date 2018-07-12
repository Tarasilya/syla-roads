#ifndef __NODE_H__
#define __NODE_H__

#include "enum.h"
#include "game_object.h"

class Node : public GameObject
{
private:
    Fraction fraction_;

public:
    Fraction GetFraction();
};


#endif // __NODE_H__
