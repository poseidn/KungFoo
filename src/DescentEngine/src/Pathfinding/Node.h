/*
Copyright (C) 2016 Thomas Hauth. All Rights Reserved.
* Written by Thomas Hauth (Thomas.Hauth@web.de)

This file is part of Kung Foo Barracuda.

Kung Foo Barracuda is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Kung Foo Barracuda is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Kung Foo Barracuda.  If not, see <http://www.gnu.org/licenses/>.
*/

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

