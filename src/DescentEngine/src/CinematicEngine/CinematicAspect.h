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

#include "../Cpp11.h"
#include "../StateEngine/Aspect.h"

#include "CinematicEngine.h"

template<class TState, class TCinEngine>
class CinematicAspect: public Aspect<TState> {
public:
	CinematicAspect(TCinEngine & ng) :
			m_engine(ng) {
	}

	virtual ~CinematicAspect() {
	}

	virtual void init(TState & state) CPP11_OVERRIDE {
		state.slotStep.subscribe([this] ( TState & g, float t)
		{	this->step(g,t);}, "CollisionAspect::step");
	}
private:
	void step(TState & gs, const float deltaT) {
		m_engine.step( deltaT );
	}

	TCinEngine & m_engine;
};
