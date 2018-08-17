#pragma once

#include "object_view.h"
#include "node.h"
#include "road.h"

#include <functional>
#include <set>

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
	std::set<int> selected_by_;

public:
	NodeView(Game* game, Node* node);
	Node* GetNode() const;

	virtual NodeView* NextVertically(int direction);
	virtual NodeView* NextHorizontally(int direction);

	virtual void RoadSelect();
	virtual bool IsRoadSelected();
	virtual RoadView* GetSelectedRoad();
	void Select(int player_id);
	void Deselect(int player_id);
};