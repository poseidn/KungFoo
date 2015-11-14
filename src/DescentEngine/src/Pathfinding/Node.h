#pragma once

#include <vector>
#include <list>

#include "../VectorTypes.h"
#include "NodeList.h"

class Node {
public:
	Node() :
			G(0.0f), F(0.0f), Previous(nullptr), Location(Vector2()) {

	}

	Node(Vector2 const& loc) :
			G(0.0f), F(0.0f), Previous(nullptr), Location(loc) {
	}

	void setBlocked() {
		F = 100000.0f;
	}

	void addNeighbour(Node * n) {
		Neighbours.push_back(n);
	}

	// overall rating of this Node
	float G;
	float F;
	NodePtrVector Neighbours;
	NodePtr Previous;
	Vector2 Location;

	// reset for new path search, neighbours will stay
	void reset() {
		Previous = nullptr;
		G = 0.0f;
		F = 0.0f;
	}

	float distanceTo(Node const* n) const {
		return distanceTo(n->Location);
	}

	float distanceTo(Vector2 const& v) const {
		const Vector2 distVec = v - this->Location;
		// don't use magSquared because we may use distances smaller than 1
		return distVec.mag();
	}
};

