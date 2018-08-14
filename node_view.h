#pragma once

#include "object_view.h"
#include "node.h"
#include "road.h"

#include <functional>

class RoadView;

class NodeView : public ObjectView {

private:
	NodeView* Next(const std::function<bool(Node*, Node*)>& less, const std::function<bool(Node*, Node*)>& same);
	bool IsInCloseRange(double base, double y);
	bool IsInDirectionFromTo(double from, double to, int direction);
	void UpdateIfBetter(NodeView*& current, Node* candidate, const std::function<bool(Node*, Node*)>& less);

protected:
	Game* game_;
	Node* node_;
	bool focused_;

public:
	NodeView(Game* game, Node* node);
	Node* GetNode() const;

	virtual NodeView* NextVertically(int direction);
	virtual NodeView* NextHorizontally(int direction);

	virtual void RoadSelect();
	virtual bool IsRoadSelected();
	virtual RoadView* GetSelectedRoad();
	void SetFocused(bool focused);
};