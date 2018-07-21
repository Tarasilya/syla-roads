#pragma once

#include "object_view.h"

class Node;

class NodeView : public ObjectView {
protected:
	bool focused_;
public:
	virtual Node* GetNode() const = 0;
	void SetFocused(bool focused);
};