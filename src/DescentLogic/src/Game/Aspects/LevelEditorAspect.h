#pragma once

#include <string>

#include <DescentEngine/src/Cpp11.h>
#include <DescentEngine/src/StateEngine/Aspect.h>

class GameState;
class LevelFactory;

class LevelEditorAspect: public Aspect<GameState> {
public:
	LevelEditorAspect(std::string const& levelName) :
			m_levelName(levelName) {
	}

	virtual ~LevelEditorAspect() = default;

	virtual void init(GameState & gs) CPP11_OVERRIDE;

private:
	void step(GameState & gs, const float deltaT);

	std::string m_levelName;
};
