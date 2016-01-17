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
