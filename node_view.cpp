#include "node_view.h"
#include "node.h"
#include "game.h"

#include <iostream>
#include <functional>
#include <cmath>

const double CLOSE_RANGE = 0.001;

NodeView::NodeView(Game* game, Node* node) : node_(node), game_(game), focused_(false) {}

NodeView* NodeView::NextHorizontally(int direction) {
	return Next(
		[direction, this](Node* a, Node* b) {
			return IsInDirectionFromTo(a->x(), b->x(), direction);
		},
		[this](Node* a, Node* b) {
			return IsInCloseRange(a->y(), b->y());
		}
	);
}

NodeView* NodeView::NextVertically(int direction) {
	return Next(
		[direction, this](Node* a, Node* b) {
			return IsInDirectionFromTo(a->y(), b->y(), direction);
		},
		[this](Node* a, Node* b) {
			return IsInCloseRange(a->x(), b->x());
		}
	);
}

NodeView* NodeView::Next(const std::function<bool(Node*, Node*)>& less, const std::function<bool(Node*, Node*)>& same) {
	const std::vector<Node*>& nodes = game_->GetNodes();

	NodeView *same_line_target = 0, *any_line_target = 0;
	for (auto node: nodes) {
		if (less(node_, node)) {
			UpdateIfBetter(any_line_target, node, less);
			if (same(node_, node)) {
				UpdateIfBetter(same_line_target, node, less);
			}
		}
	}

	if (same_line_target == 0) {
		return any_line_target == 0 ? this : any_line_target;
	}
	else {
		return same_line_target == 0 ? this : same_line_target;
	}

}

void NodeView::UpdateIfBetter(NodeView*& current, Node* candidate, const std::function<bool(Node*, Node*)>& less) {
	if (current == 0 || less(candidate, current->GetNode())) {
		current = (NodeView*) candidate->GetView(game_);
	}
}

bool NodeView::IsInCloseRange(double base, double y) {
	return std::abs(base - y) < CLOSE_RANGE;
}

bool NodeView::IsInDirectionFromTo(double from, double to, int direction) {
	return (to - from) * direction > 0;
}

Node* NodeView::GetNode() const {
	return node_;
}

void NodeView::SetFocused(bool focused) {
	focused_ = focused;
}

void NodeView::RoadSelect() {
	// do nothing for general node
}

bool NodeView::IsRoadSelected() {
	return false;
}