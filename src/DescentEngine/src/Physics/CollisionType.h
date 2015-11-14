#pragma once

enum class CollisionType {
	// no collisions performed
	NoCollideLike,

	// dynamic moving object with a circle collision shape
	CircleDynamic,

	// static object ( just collides ) with boxed collision shape
	BoxStatic
};
