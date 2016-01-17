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

#include <DescentEngine/src/Pathfinding/Pathfinding.h>
#include <DescentEngine/src/Pathfinding/Node.h>

TEST(PathfindingTest, easyPath) {
	Node n_1_1( Vector2(1,1));
	Node n_1_2( Vector2(1,2));
	Node n_2_1( Vector2(2,1));
	Node n_2_2( Vector2(2,2));
	Node n_3_1( Vector2(3,1));
	Node n_3_2( Vector2(3,2));

	n_1_1.addNeighbour( &n_1_2 );
	n_1_1.addNeighbour( &n_2_1 );
	n_1_1.addNeighbour( &n_2_2 );

	n_1_2.addNeighbour( &n_1_1 );
	n_1_2.addNeighbour( &n_2_1 );
	n_1_2.addNeighbour( &n_2_2 );

	n_2_1.addNeighbour( &n_3_1 );
	n_2_1.addNeighbour( &n_3_2 );
	n_2_1.addNeighbour( &n_2_2 );
	// back ...
	n_2_1.addNeighbour( &n_1_1 );
	n_2_1.addNeighbour( &n_1_2 );

	n_2_2.addNeighbour( &n_3_1 );
	n_2_2.addNeighbour( &n_3_2 );
	n_2_2.addNeighbour( &n_2_1 );
	// back ...
	n_2_2.addNeighbour( &n_1_1 );
	n_2_2.addNeighbour( &n_1_2 );

	n_3_1.addNeighbour( &n_3_2 );
	// back ...
	n_3_1.addNeighbour( &n_2_1 );
	n_3_1.addNeighbour( &n_2_2 );

	n_3_2.addNeighbour( &n_3_1 );
	// back ...
	n_3_2.addNeighbour( &n_2_1 );
	n_3_2.addNeighbour( &n_2_2 );

	AStar star;
	auto path =star.pathToNode( &n_1_1, &n_3_2 );

	ASSERT_EQ( path.size(), size_t(3));

}
