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
#include <DescentEngine/src/VectorTypes.h>
#include <DescentEngine/src/StateEngine/Aspect.h>

class GameState;
class LevelFactory;

class FreeScrollingAspect: public Aspect<GameState> {
public:
	FreeScrollingAspect() {
	}

	virtual ~FreeScrollingAspect() {
	}

	virtual void init(GameState & gs) CPP11_OVERRIDE;

private:
	void playerMove(GameState & gs, Vector2 const& v);

	void step(GameState & gs, const float deltaT);

};
