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
#include <DescentEngine/src/StateEngine/Aspect.h>
#include <DescentLogic/src/Game/GameState.h>

class DebugVisualCollisionsAspect: public Aspect<GameState> {
public:
	DebugVisualCollisionsAspect() {
	}

	virtual ~DebugVisualCollisionsAspect() {
	}

	virtual void init(GameState & gs) CPP11_OVERRIDE
	{
		// todo: also listen on "entity removed" and remove the debug visual again
		gs.slotEntityAdded.subscribe([this ]( GameState & g, Entity * ent)
		{	this->entityAdded(g, ent);});
	}

private:
	//void step(GameState & gs, const float deltaT);

	void entityAdded(GameState & gs, Entity * ent) {
		if (ent->doesCollide() && (ent->getCollisionType() == CollisionType::BoxStatic)) {
			logging::Info() << "setting up debug visual ";

			// add debug visual
			auto tex = gs.getEngines().resourceEngine().loadImage("collision_box");
			SpriteVisual pVisual(gs.getEngines().renderEngine().getScreenTransform(), tex, ent->getPosition(),
					ent->getBoundingBox().getSize(), LayerPriorityMax);

			gs.getEngines().renderEngine().addSpriteVisual(pVisual);
		}
	}

};
