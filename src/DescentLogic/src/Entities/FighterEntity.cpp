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

#include "FighterEntity.h"
#include "../Config/PlayerMovement.h"
#include "../Config/GameRules.h"
#include <boost/math/constants/constants.hpp>

#include <DescentEngine/src/EntityEngine/EntityEngine.h>
#include <DescentEngine/src/Pathfinding/Pathfinding.h>
#include <DescentEngine/src/Pathfinding/Node.h>
#include <DescentEngine/src/Timing.h>
#include <DescentEngine/src/Cpp11.h>

FighterEntity::FighterEntity(Vector2 intialPosition, Rectangle2 boundingBox) :
		MultiVisualEntity(intialPosition, boundingBox), m_dead(false), m_life(GameRules::FighterLife), m_attackTime(
				EnemyBehaviour::AttacDelay), m_lastHit(-1.0f) {
	m_doesCollisionStick = true;
	setCollisionGroup(GameCollisionGroups::Characters);
	setCollisionMask(GameCollisionGroups::Characters_CollidesWith);
}

int FighterEntity::getCurrentSekktor() const {
	auto dir = getDirection();

	float cosPhi = acos(dir.y());
	// handle left sektor
	if (dir.x() < 0.0f) {
		cosPhi = boost::math::constants::pi<float>() + boost::math::constants::pi<float>() - cosPhi;
	}
	float sektor = (cosPhi / (2.0f * boost::math::constants::pi<float>())) * 8.0f;
	// rotate, so the up / down position will be in the middle of a sekktor
	// and not on the border
	sektor += 0.5f;
	// handle wrap around
	if (sektor < 0.0f) {
		sektor = std::fabs(0.5f + sektor);
	}
	if (sektor >= 8.0f) {
		sektor = 0.0f;
	}

	return std::floor(sektor);
}

void FighterEntity::updateVisual(Engines & eg) {
	const int sekktor = getCurrentSekktor();

	if (isDead()) {
		changeActiveVisual(eg, DescentTextureIds::Dead_0 + sekktor);
	} else if (getJumpAction().isActive()) {
		changeActiveVisual(eg, DescentTextureIds::Jump_0 + sekktor);
	} else if (getKickAction().isActive()) {
		changeActiveVisual(eg, DescentTextureIds::Kick_0 + sekktor);
	} else if (getHitAction().isActive()) {
		changeActiveVisual(eg, DescentTextureIds::Hit_0 + sekktor);
		// todo: use movement here so only walk when we actually move
	} else if (wasMoved()) {
		changeActiveVisual(eg, DescentTextureIds::Walk_0 + sekktor);
	} else {
		// idle animation
		// todo: call only when needed
		changeActiveVisual(eg, DescentTextureIds::Stand_0 + sekktor);
	}
}

void FighterEntity::validateActions(float deltaT, float hitRegenTime) {
	// todo: not so nice, make this more generic
	getJumpAction().validate(deltaT, PlayerMovement::JumpRegenerationTime);
	getKickAction().validate(deltaT, PlayerMovement::JumpRegenerationTime);
	getHitAction().validate(deltaT, hitRegenTime);
}

void FighterEntity::die() {
	m_dead = true;
	setCollisionGroup(GameCollisionGroups::CharactersDead);
	setCollisionMask(GameCollisionGroups::CharactersDead_CollidesWith);
	logging::Debug() << "A Fighter died !";
}

float FighterEntity::runTo(Vector2 location, float maxSpeed, float deltaT, EntityEngine & entNG,
		float closeThreshold) {

	CPP11_CONSTEXPR	float minimumMoveSq(util::sq(0.1f));

	// we are almost there already ...
	if (util::withinDelta(getPosition(), location, minimumMoveSq)) {
		return 0.0f;
	}

	bool runPathfinding = true;

	if (m_nextNode.isValid())
		if (!util::withinDelta(getPosition(), m_nextNode.getValue(), minimumMoveSq)) {
			// just move further to the last node found
			// not close enough to this node, yet
			runPathfinding = false;
		}

	if (runPathfinding) {
		Pathfinding & finding = entNG.getPathfinding();

		Node * startNode = entNG.findClosestNode(this->getPosition());
		Node * endNode = entNG.findClosestNode(location);

		assert(startNode);
		assert(endNode);

		//Timing tm;
		finding.reset();
		finding.resetNodes(entNG.getPathfindingNodes());
		const auto path = finding.pathToNode(startNode, endNode);
		//float dt = tm.end();
		//logging::Info() << "Pathfinding took " << dt << " seconds";

		// move to the next node:
		const float distToTarget = startNode->distanceTo(endNode);
		if (path.size() > 1) {
			const Vector2 nextLocation = path[1]->Location;
			m_nextNode.setValue(nextLocation);
		} else {
			m_nextNode.invalidate();
			return 0.0f;
		}
	}
	const Vector2 conVector(m_nextNode.getValue() - getPosition());
	const float dist = conVector.mag();
	const Vector2 dir = conVector.normalizedCopy();

	if (dir.nonZero()) {
		const float maxSpeedPerTimeStep = maxSpeed * deltaT;

		const Vector2 maxMove = dir * maxSpeedPerTimeStep;
		setDirection(dir);
		setMoveDelta(maxMove);
	}

	const float distToTarget = (getPosition() - location).mag();

	return distToTarget;
}

