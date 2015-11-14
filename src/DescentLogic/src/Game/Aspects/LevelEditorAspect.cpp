#include "LevelEditorAspect.h"

#include "../GameState.h"
#include "../../Entities/PlayerEntity.h"
#include "../../Config/GameMovement.h"

#include "../../LevelFactory.h"

void LevelEditorAspect::init(GameState & gs) {
	gs.slotStep.subscribe([this] ( GameState & g, float t)
	{	this->step(g,t);},"LevelEditorAspect.step");

	gs.slotActivateState.subscribe([this] (GameState & g, StateChangeInfoPtr const&) {
		g.getLevelFactory()->loadFragment( g, m_levelName );

		g.getEngines().renderEngine().setCameraLocation(
				Vector3 ( 9.0f, -2.0f, 0.0f)
		);

		// load one player
			EntityFactory fact ( g.getEngines());
			auto ent = fact.createMultiVisual<PlayerEntity>( "player1" , Vector2::Unit(),
					LayerPriorityTopMost);
			ent->changeActiveVisual(g.getEngines(), DescentTextureIds::Walk_0);

			PlayerData pd( ent.get(), 0 );
			g.getPlayers().push_back( pd );

			g.addEntity(std::move(ent));

		});

	gs.slotDebugSwitchScrolling.subscribe([this ]( GameState & g, bool enabled)
	{});
}

void LevelEditorAspect::step(GameState & gs, float deltaT) {
	// not filled, yet
}

