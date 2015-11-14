#pragma once

#include <DescentEngine/src/Cpp11.h>
#include <DescentEngine/src/StateEngine/Aspect.h>
#include <DescentLogic/src/Game/GameState.h>

class DebugVisualCollisionsAspect: public Aspect<GameState> {
public:
	DebugVisualCollisionsAspect() {
	}

	virtual ~DebugVisualCollisionsAspect() {
	}

	virtual void init(GameState & gs) CPP11_OVERRIDE
	{
		// todo: also listen on "entity removed" and remove the debug visual again
		gs.slotEntityAdded.subscribe([this ]( GameState & g, Entity * ent)
		{	this->entityAdded(g, ent);});
	}

private:
	//void step(GameState & gs, const float deltaT);

	void entityAdded(GameState & gs, Entity * ent) {
		if (ent->doesCollide() && (ent->getCollisionType() == CollisionType::BoxStatic)) {
			logging::Info() << "setting up debug visual ";

			// add debug visual
			auto tex = gs.getEngines().resourceEngine().loadImage("collision_box");
			SpriteVisual pVisual(gs.getEngines().renderEngine().getScreenTransform(), tex, ent->getPosition(),
					ent->getBoundingBox().getSize(), LayerPriorityMax);

			gs.getEngines().renderEngine().addSpriteVisual(pVisual);
		}
	}

};
