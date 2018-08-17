#include "node.h"

double Node::x() {
	return x_;
}

double Node::y() {
	return y_;
}

double Node::GetSyla() {
	return 0;
}

Player* Node::GetOwner()
{
	return owner_;
}