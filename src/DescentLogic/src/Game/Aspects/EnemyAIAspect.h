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

#include <list>
#include <functional>

#include <DescentEngine/src/Cpp11.h>
#include <DescentEngine/src/StateEngine/Aspect.h>

class GameState;
class PlayerEntity;

class EnemyAIAspect: public Aspect<GameState> {
public:
	EnemyAIAspect() :
			m_bEnemyAttack(true) {
	}

	virtual ~ EnemyAIAspect() {
	}

	virtual void init(GameState & gs) CPP11_OVERRIDE;

	void switchScrolling(GameState & gs) {
		// don't make do this right now, because the enemies will not attack if
		// the app is started up with no scrolling
		//m_bEnemyAttack = !m_bEnemyAttack;
	}
private:
	void step(GameState & gs, const float deltaT);
	bool m_bEnemyAttack;

};
