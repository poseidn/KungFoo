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
