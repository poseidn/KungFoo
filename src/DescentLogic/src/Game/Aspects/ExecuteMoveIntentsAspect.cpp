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

#include "ExecuteMoveIntentsAspect.h"

#include "../GameState.h"
#include "../../Entities/PlayerEntity.h"

#include <DescentEngine/src/EntityEngine/MoveAccessClass.h>

void ExecuteMoveIntentsAspect::init(GameState & gs)
{
	gs.slotStep.subscribe([this] ( GameState & g, float t)
	{	this->step(g,t);}, "ExecuteMoveIntentsAspect.step");
}

void ExecuteMoveIntentsAspect::step(GameState & gs, float deltaT)
{
/*
 * not needed any more, done by EntityEngine
 * 	make for all !
	if ( gs.getPlayerEntity() == nullptr )
		return;

	MoveAccessClass::applyMoveIntent(*gs.getPlayerEntity());*/
}

