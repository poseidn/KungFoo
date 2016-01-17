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
#include <DescentLogic/src/Game/GameState.h>

class MenuState;
class TextVisual;
class Entity;
//class StateChangeInfo;

enum class ScriptImplements {
	Step, OnScoreIncrease
};
/*
template<class TAspect>
class ScriptAspect: public Aspect<TAspect> {
public:

	typedef std::vector<ScriptImplements> ImplementsList;

	ScriptAspect(std::string const & scriptName, ImplementsList impList) :
			m_impList(impList), m_scriptName(scriptName) {
	}

	virtual void init(TAspect & gs) CPP11_OVERRIDE
	{
		m_script = gs.getEngines().scriptEngine().loadScript(m_scriptName);

		for (auto const & si : m_impList) {

			if (si == ScriptImplements::Step) {
				gs.slotStep.subscribe([&] ( TAspect & gs, float deltaT )
				{
					m_script.callFunction( "step", &gs, deltaT );
				});
			}

			addTemplated(gs, si, m_script);
		}
	}

private:

	void addTemplated(TAspect & gs, ScriptImplements si, Script & s);

	std::string m_scriptName;
	Script m_script;
	ImplementsList m_impList;
};

template<class TAspect>
void ScriptAspect<TAspect>::addTemplated(TAspect & gs, ScriptImplements si, Script & s) {
	// nothing done here
}

template<>
void ScriptAspect<GameState>::addTemplated(GameState & gs, ScriptImplements si, Script & s) {
	std::cout << "ScriptAspect<GameState>::addTemplated" << std::endl;
	if (si == ScriptImplements::OnScoreIncrease) {
		gs.slotScoreIncrease.subscribe([&] ( GameState & gs, PlayerId pid, size_t prev, size_t now )
		{
			s.callFunction
			< GameState * , PlayerId, size_t, size_t >
			( "onScoreIncrease", &gs, pid, prev, now );
		});
	}
}
*/
