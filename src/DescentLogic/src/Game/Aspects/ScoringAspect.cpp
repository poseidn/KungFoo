#include "ScoringAspect.h"

#include <DescentEngine/src/Log.h>

#include "../GameState.h"
#include "../../Config/GameRules.h"

void ScoringAspect::init(GameState & gameState) {
	gameState.slotStep.subscribe([=] ( GameState & gs, float deltaT)
	{
		if ( this->m_increaseScoreTick.validate( deltaT) )
		{
			gs.increaseScoreAllPlayers( GameRules::ScorePerSecond );
		}

	}, "ScoringAspect.step");
}

