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

#include <map>
#include <tuple>
#include <vector>
#include <memory>

#include <boost/noncopyable.hpp>

#include "../Cpp11.h"
#include "../Util.h"
#include "../Log.h"
#include "../VectorTypes.h"
#include "CollisionType.h"

class btRigidBody;
class b2World;
class b2Body;

typedef b2Body PhysicsBody;

class Entity;

// PhysicsEngine which uses bullet physics as a backend for collision and dynamics
// bullet is "tricked" to move our entities just by the move intents by setting the
// linear velocity before the step simulation to exactly the velocity neede to move to the
// new location
class PhysicsEngineBox2D: boost::noncopyable {
public:
	PhysicsEngineBox2D();
	~PhysicsEngineBox2D();

	void registerEntity(Entity * ent);

	void unregisterEntity(Entity * ent, bool allowNotFound = false);

	void step(float dt);

	size_t getRegisteredEntitiesCount() const;
	size_t getRegisteredDynamicsEntitiesCount() const;

private:

	template<class TFilter, class TEnt>
	void setFilterData(TFilter & f, TEnt * ent) {
		f.categoryBits = ent->collisionGroup();
		f.maskBits = ent->collisionMask();
	}

	void removeBodyByEntity(Entity * ent);

	struct BodiesEntry {

		BodiesEntry(b2Body * gb) :
				RigidBody(gb), LimitedLifetime(false), PhysicsLifetime(0.0f) {

		}

		BodiesEntry(b2Body * gb, float lifetime) :
				RigidBody(gb), PhysicsLifetime(lifetime) {
			LimitedLifetime = (lifetime > 0.0f);
		}

		void setLimitedLifetime(const float ttl) {
			LimitedLifetime = true;
			PhysicsLifetime = ttl;
		}

		b2Body * RigidBody;

		// certain enties might only be active in the physics system for a certain time
		// if this is > 0.0f, the lifetime of this item is limited
		bool LimitedLifetime;
		float PhysicsLifetime;
	};

	typedef std::vector<BodiesEntry> BodiesList;

	void unregisterAllEntities();

	BodiesList m_bodiesDynamic;
	BodiesList m_bodiesAll;

	uniq<b2World> m_b2world;

};

