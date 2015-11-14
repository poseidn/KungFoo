#include "ForwardScrollingAspect.h"

#include "../GameState.h"
#include "../../Entities/PlayerEntity.h"
#include "../../Config/GameMovement.h"

#include "../../LevelFactory.h"

#include <DescentEngine/src/Performance/SectionTimer.h>

void ForwardScrollingAspect::init(GameState & gs) {
	gs.slotStep.subscribe([this] ( GameState & g, float t)
	{	this->step(g,t);}, "ForwardScrollingAspect.step");

	gs.slotDebugSwitchScrolling.subscribe([this ]( GameState & g, bool enabled)
	{	this->switchScrolling(g);});

	gs.slotActivateState.subscribe([=] ( GameState & g, StateChangeInfoPtr const& ci )
	{});

}

void ForwardScrollingAspect::step(GameState & gs, float deltaT) {

	if (gs.getDelayedScrolling() > 0.0f) {
		const float ds = gs.getDelayedScrolling() - deltaT;
		gs.setDelayedScrolling(ds);
		if (ds < 0.0f) {
			gs.setScrollActive();
		}
	} else {
		if (m_scrollEnabled && gs.getScrollActive()) {
			const float streamingBufferSize = 20.0f;

			Vector3 vec = gs.getEngines().renderEngine().getCameraLocation();
			vec.setY(vec.y() + deltaT * GameMovement::ScrollSpeed);
			gs.getEngines().renderEngine().setCameraLocation(vec);

			{
				SectionTimer tm(GlobalTimingRepo::Rep, "ForwardScrollingAspect.nextLayers");
				// will automatically detect if we need a new level fragment
				gs.getLevelFactory()->nextLayers(gs, vec.y());
			}

			{
				SectionTimer tm(GlobalTimingRepo::Rep, "ForwardScrollingAspect.cleanStaticBelow");
				// remove old stuff
				gs.getEngines().entityEngine().cleanStaticBelow(vec.y() - streamingBufferSize,
						gs.getEngines());
			}
		}
	}
}

void ForwardScrollingAspect::switchScrolling(GameState & gs) {
	m_scrollEnabled = !m_scrollEnabled;
}

