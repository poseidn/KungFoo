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

#include "FreeScrollingAspect.h"

#include "../GameState.h"
#include "../../Entities/PlayerEntity.h"
#include "../../Config/GameMovement.h"

#include <DescentLogic/src/LevelFactory.h>

void FreeScrollingAspect::init(GameState & gs) {
	gs.slotStep.subscribe([this] ( GameState & g, float t)
	{	this->step(g,t);}, "FreeScrollingAspect.step");

	gs.slotPlayerMove.subscribe([this] ( GameState & g, Vector2 const& v ,  PlayerId )
	{	this->playerMove(g,v );});

}

void FreeScrollingAspect::playerMove(GameState & gs, Vector2 const& v) {
	Vector3 vec = gs.getEngines().renderEngine().getCameraLocation();
	vec.setY(vec.y() + 0.002f * v.y());
	gs.getEngines().renderEngine().setCameraLocation(vec);

}

void FreeScrollingAspect::step(GameState & gs, float deltaT) {

// clean-up old entities
//gs.getEngines().entityEngine().cleanBelow ( gs.getPlayerEntity()->getPosition().y - 20.0f );
}

