#include "FreeScrollingAspect.h"

#include "../GameState.h"
#include "../../Entities/PlayerEntity.h"
#include "../../Config/GameMovement.h"

#include <DescentLogic/src/LevelFactory.h>

void FreeScrollingAspect::init(GameState & gs) {
	gs.slotStep.subscribe([this] ( GameState & g, float t)
	{	this->step(g,t);}, "FreeScrollingAspect.step");

	gs.slotPlayerMove.subscribe([this] ( GameState & g, Vector2 const& v ,  PlayerId )
	{	this->playerMove(g,v );});

}

void FreeScrollingAspect::playerMove(GameState & gs, Vector2 const& v) {
	Vector3 vec = gs.getEngines().renderEngine().getCameraLocation();
	vec.setY(vec.y() + 0.002f * v.y());
	gs.getEngines().renderEngine().setCameraLocation(vec);

}

void FreeScrollingAspect::step(GameState & gs, float deltaT) {

// clean-up old entities
//gs.getEngines().entityEngine().cleanBelow ( gs.getPlayerEntity()->getPosition().y - 20.0f );
}

