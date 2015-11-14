#pragma once

#include <vector>

#include <DescentEngine/src/Cpp11.h>
#include <DescentEngine/src/StateEngine/Aspect.h>
#include <DescentEngine/src/StateEngine/StateChangeInfo.h>
#include <DescentEngine/src/Visuals/VisualSupport.h>

class MenuState;
class TextVisual;
class Entity;

class DebugRenderAspect: public Aspect<MenuState> {
public:
	DebugRenderAspect() {
	}

	virtual void init(MenuState & gs) CPP11_OVERRIDE {
		gs.slotActivateState.subscribe([&] ( MenuState & gs, StateChangeInfoPtr const& changeInfo )
		{
			logging::Info() << "setting up Render Debug state";
			// call this, once the screen transform is available
				gs.getEngines().renderEngine().setCameraLocation(Vector3(0.0f, 0.0f, 0.0f));
				auto trans = gs.getEngines().renderEngine().getScreenTransform();

				EntityFactory fact(gs.getEngines());
				auto logoEntity = fact. createFromTemplateName< SingleVisualEntity>("game_logo",
						Vector2(1.0f, 1.0f));
				logoEntity->getActiveVisual().get().setIngame(trans, Vector2(0.0f, 5.0f), false);
				VisualSupport::placeXCenter( logoEntity.get(), 0.5f, 0.75f, trans );
				gs.getEngines().entityEngine().addEntity(std::move(logoEntity), &gs.getManagedEntityList());

			});
	}

};
