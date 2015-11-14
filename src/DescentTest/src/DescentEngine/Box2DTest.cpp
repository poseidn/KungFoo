#include <array>
#include <tuple>

#include <gtest/gtest.h>

#include <Box2D/Box2D.h>
#include <DescentLogic/src/Entities/GameCollisionGroups.h>

TEST(Box2DTest, collide_circles) {

	b2World world(b2Vec2_zero);

	std::array<std::tuple<b2Body *, b2Vec2, float>, 2> bodies = { {
	// first circle, this one is moving
			std::make_tuple(nullptr, b2Vec2(2.0f, 2.0f), 1.0f),
			// second circle, this one is static and very heavy
			std::make_tuple(nullptr, b2Vec2(5.0f, 2.0f), 100000.0f) } };

	const float radius = 1.0f;

	for (auto & bd : bodies) {
		b2BodyDef newBody;
		newBody.position = std::get < 1 > (bd);
		newBody.type = b2_dynamicBody;

		std::get < 0 > (bd) = world.CreateBody(&newBody);

		b2CircleShape circleShape;
		circleShape.m_radius = radius;

		b2FixtureDef def;
		def.shape = &circleShape;
		def.density = std::get < 2 > (bd);
		def.filter.groupIndex = GameCollisionGroups::Characters;
		def.filter.categoryBits = GameCollisionGroups::Characters_CollidesWith;

		std::get < 0 > (bd)->CreateFixture(&def);
	}

	std::get < 0 > (bodies[0])->SetLinearVelocity(b2Vec2(0.2f, 0.0f));

	const size_t simulateSteps = 10;
	for (size_t i = 0; i < simulateSteps; i++) {

		world.Step(1.0 / 60.0, 5, 5);
	}

	// did they collide ? meaning the first circle could not pass to the other side
	ASSERT_LE(std::get < 0 > (bodies[0])->GetTransform().p.x, 4.0f);

	for (auto & bd : bodies) {
		world.DestroyBody(std::get < 0 > (bd));
	}
}

