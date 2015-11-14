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
