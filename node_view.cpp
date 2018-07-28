#include "node_view.h"
#include "game/node.h"
#include "game.h"

NodeView::NodeView(Game* game, Node* node) : node_(node), game_(game), focused_(false) {}

NodeView* NodeView::NextHorizontally(int direction) {
	const std::vector<Node*>& nodes = game_->GetNodes();

	NodeView* target = 0;
	for (auto node: nodes) {
		if (IsInCloseRange(GetNode()->y(), node->y()) && IsInDirectionFromTo(GetNode(), node, direction)) {
			if (target == 0 || IsInDirectionFromTo(node, target->GetNode(), direction)) {
				target = (NodeView*) node->GetView(game_);
			}
		}
	}

	return target == 0 ? this : target;
}

NodeView* NodeView::NextVertically(int direction) {
	throw 1;
}

bool NodeView::IsInCloseRange(int base, int y) {
	return true;
}

bool NodeView::IsInDirectionFromTo(Node* from, Node* to, int direction) {
	return (to->x() - from->x()) * direction > 0;
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