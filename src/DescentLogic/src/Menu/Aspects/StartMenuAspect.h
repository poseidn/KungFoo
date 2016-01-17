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

class MenuState;
class TextVisual;
class Entity;
//class StateChangeInfo;

class StartMenuAspect: public Aspect<MenuState> {
public:
	StartMenuAspect() :
			m_gameOverVisual(nullptr), m_scoreVisual(nullptr), m_logoEntity(nullptr), m_controlsEntity(
					nullptr), m_delayedGameOver(-1.0f) {
	}

	virtual void init(MenuState & gs) CPP11_OVERRIDE;

	TextVisual * m_gameOverVisual = nullptr;
	TextVisual * m_scoreVisual = nullptr;
	TextVisual * m_twitterUser = nullptr;
	Entity * m_logoEntity;
	Entity * m_controlsEntity;



	float m_delayedGameOver;
};
