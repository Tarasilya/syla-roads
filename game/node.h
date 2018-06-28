#ifndef __NODE_H__
#define __NODE_H__

#include "enum.h"

class Node : public GameObject
{
private:
    NodeType type_;
    Fraction entity_; // Player1, Player2, Neutral

public:
    Fraction GetPlayer();
    NodeType GetType();
};


#endif // __NODE_H__
