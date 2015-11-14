#pragma once

#include <DescentEngine/src/Cpp11.h>
#include <DescentEngine/src/StateEngine/Aspect.h>

#include <DescentEngine/src/Visuals/TextVisual.h>

class GameState;

class StatusAspect: public Aspect<GameState> {
public:
	StatusAspect() :
			m_respawnCounter(nullptr) /*:

	 m_counter(0), m_summer(0.0), m_scoreSummer(0.0f)*/{
	}

	virtual void init(GameState & gs) CPP11_OVERRIDE;

private:
	/*int m_counter;
	 float m_summer;

	 float m_scoreSummer;*/
	TextVisual * m_respawnCounter;
};
