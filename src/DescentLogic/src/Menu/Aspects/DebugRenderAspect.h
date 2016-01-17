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

#include <vector>

#include <DescentEngine/src/Cpp11.h>
#include <DescentEngine/src/StateEngine/Aspect.h>
#include <DescentEngine/src/StateEngine/StateChangeInfo.h>
#include <DescentEngine/src/Visuals/VisualSupport.h>

class MenuState;
class TextVisual;
class Entity;

class DebugRenderAspect: public Aspect<MenuState> {
public:
	DebugRenderAspect() {
	}

	virtual void init(MenuState & gs) CPP11_OVERRIDE {
		gs.slotActivateState.subscribe([&] ( MenuState & gs, StateChangeInfoPtr const& changeInfo )
		{
			logging::Info() << "setting up Render Debug state";
			// call this, once the screen transform is available
				gs.getEngines().renderEngine().setCameraLocation(Vector3(0.0f, 0.0f, 0.0f));
				auto trans = gs.getEngines().renderEngine().getScreenTransform();

				EntityFactory fact(gs.getEngines());
				auto logoEntity = fact. createFromTemplateName< SingleVisualEntity>("game_logo",
						Vector2(1.0f, 1.0f));
				logoEntity->getActiveVisual().get().setIngame(trans, Vector2(0.0f, 5.0f), false);
				VisualSupport::placeXCenter( logoEntity.get(), 0.5f, 0.75f, trans );
				gs.getEngines().entityEngine().addEntity(std::move(logoEntity), &gs.getManagedEntityList());

			});
	}

};
