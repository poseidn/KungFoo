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
