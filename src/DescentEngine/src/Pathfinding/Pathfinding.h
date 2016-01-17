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

#include <deque>

#include <boost/noncopyable.hpp>

#include "../Cpp11.h"
#include "../Log.h"

/*
 * Possible speed improvements:
 *  - grid-based fast lookup for nodes according to their position in space
 *  - fixed number of possible Neigbours ( array / std::vec ) of 6
 */

#include "NodeList.h"

// Astar wayfinding algorithm within a node graph
class AStar {
public:

	// reset the internal state of this astar algo
	// must be done before using it
	void reset();

	// reset the status of the nodes, must be done before using them
	void resetNodes(NodeVector & nodes);

	std::deque<Node*> pathToNode(Node * startNode, Node * targetNode);

private:

	// find the way back along the shortest path and compile the step
	// into the "path" deque
	void backtrack(Node * child, std::deque<Node*> & path);

	// evaluate all neighbors and compute their rating
	void expandNode(Node * parent, Node * targetNode);

	// nodes which have not been visited yet
	NodeList OpenList;
	// nodes which have already been visited
	NodeList ClosedList;
};

// use the Astar as default pathfinding
using Pathfinding = AStar;
