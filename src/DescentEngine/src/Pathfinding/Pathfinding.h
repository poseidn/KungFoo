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
class AStar: boost::noncopyable {
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
class Pathfinding CPP11_FINAL : public AStar {
};

