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

#include "LevelEditorAspect.h"

#include "../GameState.h"
#include "../../Entities/PlayerEntity.h"
#include "../../Config/GameMovement.h"

#include "../../LevelFactory.h"

void LevelEditorAspect::init(GameState & gs) {
	gs.slotStep.subscribe([this] ( GameState & g, float t)
	{	this->step(g,t);},"LevelEditorAspect.step");

	gs.slotActivateState.subscribe([this] (GameState & g, StateChangeInfoPtr const&) {
		g.getLevelFactory()->loadFragment( g, m_levelName );

		g.getEngines().renderEngine().setCameraLocation(
				Vector3 ( 9.0f, -2.0f, 0.0f)
		);

		// load one player
			EntityFactory fact ( g.getEngines());
			auto ent = fact.createMultiVisual<PlayerEntity>( "player1" , Vector2::Unit(),
					LayerPriorityTopMost);
			ent->changeActiveVisual(g.getEngines(), DescentTextureIds::Walk_0);

			PlayerData pd( ent.get(), 0 );
			g.getPlayers().push_back( pd );

			g.addEntity(std::move(ent));

		});

	gs.slotDebugSwitchScrolling.subscribe([this ]( GameState & g, bool enabled)
	{});
}

void LevelEditorAspect::step(GameState & gs, float deltaT) {
	// not filled, yet
}

