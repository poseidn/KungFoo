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
