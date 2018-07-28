#pragma once

#include "object_view.h"
#include "game/node.h"

class NodeView : public ObjectView {
protected:
	Game* game_;
	Node* node_;
	bool focused_;

	bool IsInCloseRange(int base, int y);
	bool IsInDirectionFromTo(Node* from, Node* to, int direction);
public:
	NodeView(Game* game, Node* node);
	Node* GetNode() const;

	NodeView* NextVertically(int direction);
	NodeView* NextHorizontally(int direction);

	virtual void RoadSelect();
	virtual bool IsRoadSelected();
	void SetFocused(bool focused);
};