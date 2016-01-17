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

#include <DescentEngine/src/CinematicEngine/CinematicEngine.h>
class IntroCinematic {
public:
	static void setup(CinematicEngine & eg) {
/*
 * not run atm !
		EntityFactory fact(eg.getEngines());
		eg.getEngines().renderEngine().setCameraLocation(Vector3(0.0f, 0.0f, 0.0f));
		auto bgEnt = fact. createFromTemplateName<SingleVisualEntity>("intro_bg", Vector2(0.0f, 10.0f));

		auto guyEnt = fact. createFromTemplateName<SingleVisualEntity>("intro_guy", Vector2(0.0f, 0.0f));
		auto guyEnt2 = fact. createFromTemplateName<SingleVisualEntity>("intro_guy", Vector2(0.0f, 0.0f));

		eg.getEngines().entityEngine().addEntity(std::move(bgEnt));
		eg.getEngines().entityEngine().addEntity(std::move(guyEnt), "guy1");
		eg.getEngines().entityEngine().addEntity(std::move(guyEnt2), "guy2");

		eg.addTimelineItem(
				std::make_shared < CinematicTransformAnimation
						> ("guy1", Vector2(0, 0), Vector2(5, 5), CinematicTimespan(2, 5)));

		eg.addTimelineItem(
				std::make_shared < CinematicTransformAnimation
						> ("guy2", Vector2(20, 0), Vector2(8, 7), CinematicTimespan(0, 3)));*/
	}
};
