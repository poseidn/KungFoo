#pragma once

#include <DescentEngine/src/Cpp11.h>
#include <DescentEngine/src/Physics/CollisionGroups.h>

struct GameCollisionGroups {

	static CPP11_CONSTEXPR short Statics = 1 << 1;
	static CPP11_CONSTEXPR short StaticsJumpable = 1 << 2;

	static CPP11_CONSTEXPR short Characters = 1 << 3;
	static CPP11_CONSTEXPR short CharactersJump = 1 << 4;

	// don't collide with other characters any more
	static CPP11_CONSTEXPR short CharactersDead = 1 << 5;

	// got a little hacking due to MSVC limitations
	static CPP11_CONSTEXPR short Statics_CollidesWith = /* CollisionGroups::Ground |*/ 1 | Characters
			| CharactersJump | CharactersDead;

	static CPP11_CONSTEXPR short StaticsJumpable_CollidesWith = /* CollisionGroups::Ground |*/ 1 | Characters
			| CharactersDead;

	static CPP11_CONSTEXPR short Characters_CollidesWith = /* CollisionGroups::Ground |*/ 1 | Statics
			| StaticsJumpable | Characters | CharactersJump;

	static CPP11_CONSTEXPR short CharactersJump_CollidesWith = /* CollisionGroups::Ground |*/ 1 | Statics
			| Characters | CharactersJump;

	static CPP11_CONSTEXPR short CharactersDead_CollidesWith = /* CollisionGroups::Ground |*/ 1 | Statics
			| StaticsJumpable;
};
