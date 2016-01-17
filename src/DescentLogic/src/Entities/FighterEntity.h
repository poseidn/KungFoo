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

#include <cmath>

#include <DescentEngine/src/EntityEngine/MultiVisualEntity.h>
#include <DescentEngine/src/EntityEngine/TimeSliceAction.h>
#include <DescentEngine/src/Util.h>
#include <DescentLogic/src/Config/EnemyBehaviour.h>


#include "GameCollisionGroups.h"
#include "TextureIds.h"

class FighterEntity: public MultiVisualEntity {
public:
	FighterEntity(Vector2 intialPosition, Rectangle2 boundingBox);

	virtual ~FighterEntity() {
	}

	virtual CollisionType getCollisionType() const CPP11_OVERRIDE {
		return CollisionType::CircleDynamic;
	}

	TimeSliceAction & getJumpAction() {
		return m_jumpAction;
	}

	TimeSliceAction & getHitAction() {
		return m_hitAction;
	}

	TimeSliceAction & getKickAction() {
		return m_kickAction;
	}

	bool decreaseLastHit(float dt) {
		if (m_lastHit < 0.0f)
			return true;

		m_lastHit -= dt;
		if (m_lastHit < 0.0f)
			return true;
		else
			return false;
	}

	void activateLastHit() {
		m_lastHit = EnemyBehaviour::RegenerationAfterHit;
	}

	virtual void validateActions(float deltaT, float hitRegenTime);

	void subtractLife(int amount) {
		m_life -= amount;
	}

	int getLife() const {
		return m_life;
	}

	bool isDead() const {
		return m_dead;
	}

	void die();

	void setDirection(Vector2 const d) {
		m_direction = d.normalizedCopy();
	}

	bool isLyingFlat() const {
		//return m_hitAction.isActive();
		return m_dead;
	}

	// let's this entity run to a position as fast as possible
	float runTo(Vector2 location, float maxSpeed, float deltaT, EntityEngine & entNG, float closeThreshold =
			0.0f);

	Vector2
	const& getDirection() const {
		return m_direction;
	}

	float getAttackTime() const {
		return m_attackTime;
	}

	void decreaseAttackTime(float by) {
		m_attackTime -= by;
	}

	virtual void updateVisual(Engines & eg);

	int getCurrentSekktor() const;

protected:
	int m_life;

private:
	TimeSliceAction m_hitAction;

	TimeSliceAction m_jumpAction;
	TimeSliceAction m_kickAction;
	Vector2 m_direction;
	bool m_dead;
	float m_attackTime;
	float m_lastHit;

	// the next node to move to, which was found by the path finding
	util::ValidValue<Vector2> m_nextNode;
}
;
