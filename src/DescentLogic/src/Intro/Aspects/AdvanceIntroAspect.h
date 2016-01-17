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

#include <DescentEngine/src/EntityEngine/TimeSliceAction.h>

#include <DescentEngine/src/Cpp11.h>
#include <DescentEngine/src/Log.h>
#include <DescentEngine/src/StateEngine/Aspect.h>

#include <DescentEngine/src/Input/InputContainer.h>
#include <DescentEngine/src/EntityEngine/EntityFactory.h>
#include <DescentLogic/src/Entities/WallEntity.h>

#include <DescentLogic/src/Intro/IntroState.h>

// translates the content of an InputContainer
// to the signals of a game state

class CinematicEngine;

class AdvanceIntroAspect: public Aspect<IntroState> {
public:

	AdvanceIntroAspect(CinematicEngine & cinEngine) :
			m_cinEngine(cinEngine) {
	}

	virtual ~AdvanceIntroAspect() {
	}

	virtual void init(IntroState & gs) CPP11_OVERRIDE;

private:

	void nextStage(IntroState & gs);

	Vector2 m_logoKungFooPos;

	TimeSliceAction m_kick;
	CinematicEngine & m_cinEngine;
};
