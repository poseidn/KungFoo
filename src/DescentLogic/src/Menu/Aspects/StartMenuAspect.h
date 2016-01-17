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
