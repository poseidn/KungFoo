#include "ExecuteMoveIntentsAspect.h"

#include "../GameState.h"
#include "../../Entities/PlayerEntity.h"

#include <DescentEngine/src/EntityEngine/MoveAccessClass.h>

void ExecuteMoveIntentsAspect::init(GameState & gs)
{
	gs.slotStep.subscribe([this] ( GameState & g, float t)
	{	this->step(g,t);}, "ExecuteMoveIntentsAspect.step");
}

void ExecuteMoveIntentsAspect::step(GameState & gs, float deltaT)
{
/*
 * not needed any more, done by EntityEngine
 * 	make for all !
	if ( gs.getPlayerEntity() == nullptr )
		return;

	MoveAccessClass::applyMoveIntent(*gs.getPlayerEntity());*/
}

