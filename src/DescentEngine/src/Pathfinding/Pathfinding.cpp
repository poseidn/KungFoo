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

#include "Pathfinding.h"

#include <algorithm>

#include "Node.h"

void AStar::resetNodes(NodeVector& nodes) {
	for (auto & n : nodes) {
		n.reset();
	}
}

void AStar::reset() {
	OpenList.clear();
	ClosedList.clear();
}

std::deque<Node*> AStar::pathToNode(Node * startNode, Node * targetNode) {

	assert(startNode != nullptr);
	assert(targetNode != nullptr);

	OpenList.clear();
	OpenList.push_back(startNode);

	int maxIterations = 10000;
	int iter = 0;

	while (OpenList.size() != 0) {
		// expand the best node on the open list

		// find smallest F
		float smallest = 1000000000.0f;
		Node * smallestN = nullptr;
		for (Node * n : OpenList) {
			if (n->F < smallest) {
				smallest = n->F;
				smallestN = n;
			}
		}

		assert(smallestN);

		//logging::Info() << "Removing node " << smallestN->Location << "from the OpenList";

		OpenList.remove(smallestN);
		ClosedList.push_back(smallestN);

		if (smallestN == targetNode) { // found
			std::deque<Node*> path;

			backtrack(targetNode, path);

			//logging::Info() << "at target node !";
			return path;
		}

		//logging::Info() << "Expanding node " << smallestN->Location << "from the OpenList";
		//if (!smallestN->isBlocked())
		expandNode(smallestN, targetNode);
		iter++;
		if (iter > maxIterations) {
			logging::Fatal() << "Pathfinding from " << startNode->Location << " to " << targetNode->Location
					<< " stopped after max iterations reached";
		}
	}

	// no path found
	return std::deque<Node*>();
}

void AStar::backtrack(Node * child, std::deque<Node*> & path) {
	path.push_front(child);
	if (child->Previous != nullptr) {
		backtrack(child->Previous, path);
	}
}

void AStar::expandNode(Node * parent, Node * targetNode) {
	if (parent->Neighbours.size() == 0) {
		//logging::Info() << "has no neihgbours";
	}

	for (Node* child : parent->Neighbours) {
		//logging::Info() << "Looking at child node " << child->Location;

		/*if (child->isBlocked())
		 continue;*/

		if (std::find(ClosedList.begin(), ClosedList.end(), child) != ClosedList.end()) {
			// been there, done it
			//logging::Info() << ">> child node in closed list)";
			continue;
		}

		/*
		 *         // wenn der Nachfolgeknoten bereits auf der Open List ist,
		 // aber der neue Weg nicht besser ist als der alte - tue nichts
		 if openlist.contains(successor) and tentative_g >= g(successor) then
		 continue
		 */
		float thisG = 1.0f + parent->G;
		child->G = thisG;

		// add heuristic, explicit weighting for different use cases may be needed here
		float thisF = thisG + targetNode->distanceTo(child);

		child->F = thisF;
		//logging::Info() << "G is " << thisG;
		//logging::Info() << "F is " << thisF;
		child->Previous = parent;

		// add to the open list?
		if (std::find(OpenList.begin(), OpenList.end(), child) == OpenList.end()) {
			OpenList.push_back(child);
			//logging::Info() << "added child to open list";
		}
	}
}
