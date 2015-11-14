#include "AdvanceIntroAspect.h"

#include "../../Common/GameToMenuInfo.h"
#include <DescentEngine/src/CinematicEngine/CinematicEngine.h>
#include <DescentEngine/src/Visuals/VisualSupport.h>

void AdvanceIntroAspect::init(IntroState & thisGs) {

	thisGs.slotInputNext.subscribe([&] ( IntroState & gs, InputSystem::ContainerId id )
	{
		logging::Info() << "going to next Intro state";
		nextStage ( gs);
	});

	thisGs.slotActivateState.subscribe([&] ( IntroState & gs, StateChangeInfoPtr const& changeInfo )
	{
		logging::Info() << "setting up Intro state";
		nextStage ( gs );
	});
}

void AdvanceIntroAspect::nextStage(IntroState & gs) {

	gs.setStage(gs.getStage() + 1);

	// remove the old stuff
	gs.getEngines().animationEngine().clearAll();
	gs.getEngines().entityEngine().cleanManagedList(gs.m_managedEntities, gs.getEngines());
	m_cinEngine.reset();
	gs.m_managedEntities.clear();

	auto lmdNextStage = [&] ( Engines & eg ) {
		this->nextStage(gs );
	};
	auto & entEngine = gs.getEngines().entityEngine();
	EntityFactory fact(gs.getEngines());

	ScreenTransform const& trans = gs.getEngines().renderEngine().getScreenTransform();

	if (gs.getStage() == 1) {
		auto logoMarker = fact. createFromTemplateName<SingleVisualEntity>("intro_logo_maker",
				Vector2(0.0f, 0.0f));
		VisualSupport::placeXCenter(logoMarker.get(), 0.5f, 0.60f, trans);

		logoMarker->getActiveVisual().get().setTransparency(0.0f);
		gs.m_managedEntities.push_back(logoMarker.get());
		entEngine.addEntity(std::move(logoMarker), "logo_maker");

		m_cinEngine.addTimelineItem(
				std::make_shared < CinematicTranspararencyAnimation
						> ("logo_maker", 0.0f, 1.0f, CinematicTimespan(0.8, 3.0)));

		// auto advance after n seconds
		m_cinEngine.addTimelineItem(
				std::make_shared < CinematicLambda > (lmdNextStage, CinematicTimepoint(5.0)));
	} else if (gs.getStage() == 2) {

		gs.getEngines().renderEngine().setCameraLocation(Vector3(0.0f, 0.0f, 0.0f));

		auto logoKungfu = fact. createFromTemplateName<SingleVisualEntity>("intro_logo_kungfoo",
				Vector2(0.0f, 0.0f));
		VisualSupport::placeXCenter(logoKungfu.get(), 0.5f, 0.60f, trans);
		/*
		 Entity * guyEnt = fact.create<  SingleVisualEntity>("intro_guy", Vector2(0.0f, 0.0f));
		 Entity * guyEnt2 = fact.create<  SingleVisualEntity>("intro_guy", Vector2(0.0f, 0.0f));
		 */
		gs.m_managedEntities.push_back(logoKungfu.get());
		logoKungfu->getActiveVisual().get().setIngame(trans, Vector2(), false);
		/*	entEngine.addEntity(guyEnt, "guy1");
		 entEngine.addEntity(guyEnt2, "guy2");
		 */

		const auto finalPos = logoKungfu->getMoveIntent();
		const Vector2 startPos = Vector2(finalPos.x(), 0);

		logoKungfu->setMoveIntent(startPos);
		logoKungfu->getActiveVisual().get().setTransparency(0.0f);

		m_cinEngine.addTimelineItem(
				std::make_shared < CinematicTransformAnimation
						> ("logo_kungfoo", startPos, finalPos, CinematicTimespan(0, 3)));
		m_cinEngine.addTimelineItem(
				std::make_shared < CinematicTranspararencyAnimation
						> ("logo_kungfoo", 0.0f, 0.9f, CinematicTimespan(1.01, 3)));

		m_logoKungFooPos = finalPos;
		entEngine.addEntity(std::move(logoKungfu), "logo_kungfoo");

		// left fist
		auto logoFistLeft = fact. createFromTemplateName<SingleVisualEntity>("intro_logo_fist_left",
				Vector2(-10.0f, 0.0f));
		logoFistLeft->getActiveVisual().get().setIngame(trans, Vector2(100.0, 0.0f), false);

		gs.m_managedEntities.push_back(logoFistLeft.get());
		entEngine.addEntity(std::move(logoFistLeft), "logo_fist_left");
		m_cinEngine.addTimelineItem(
				std::make_shared < CinematicTransformAnimation
						> ("logo_fist_left", Vector2(-2.0, m_logoKungFooPos.y()), Vector2(
								m_logoKungFooPos.x() - 6.3f, m_logoKungFooPos.y()), CinematicTimespan(4.3, 4.8)));
		m_cinEngine.addTimelineItem(
				std::make_shared < CinematicTranspararencyAnimation
						> ("logo_fist_left", 0.0f, 1.0f, CinematicTimespan(4.301, 4.5)));
		m_cinEngine.addTimelineItem(
				std::make_shared < CinematicSound > ("player_kick1", CinematicTimepoint(4.75)));

		// rigth fist
		auto logoFistRight = fact. createFromTemplateName<SingleVisualEntity>("intro_logo_fist_right",
				Vector2(300.0f, 3.0f));
		logoFistRight->getActiveVisual().get().setIngame(trans, Vector2(), false);
		gs.m_managedEntities.push_back(logoFistRight.get());
		entEngine.addEntity(std::move(logoFistRight), "logo_fist_right");
		m_cinEngine.addTimelineItem(
				std::make_shared < CinematicTransformAnimation
						> ("logo_fist_right", Vector2(m_logoKungFooPos.x() + 9.8f, m_logoKungFooPos.y()), Vector2(
								m_logoKungFooPos.x() + 6.3f, m_logoKungFooPos.y()),
						//Vector2(0.0, m_logoKungFooPos.y()), Vector2(0.0f, m_logoKungFooPos.y()),
						CinematicTimespan(4.9, 5.4)));
		m_cinEngine.addTimelineItem(
				std::make_shared < CinematicTranspararencyAnimation
						> ("logo_fist_right", 0.0f, 1.0f, CinematicTimespan(4.91, 5.1)));
		m_cinEngine.addTimelineItem(
				std::make_shared < CinematicSound > ("player_kick1", CinematicTimepoint(5.3)));

		// barracuda
		auto logoBarPos = Vector2(m_logoKungFooPos.x() - 0.0f, m_logoKungFooPos.y() - 3.4f);

		auto logoBar = fact. createFromTemplateName<SingleVisualEntity>("intro_logo_bar", logoBarPos);
		logoBar->getActiveVisual().get().setIngame(trans, logoBarPos, false);
		logoBar->getActiveVisual().get().setTransparency(0.0f);
		gs.m_managedEntities.push_back(logoBar.get());
		entEngine.addEntity(std::move(logoBar), "logo_bar");
		/*m_cinEngine.addTimelineItem(
		 new CinematicTransformAnimation("logo_bar",
		 Vector2(m_logoKungFooPos.x(), m_logoKungFooPos.y() - 10.0f),
		 Vector2(m_logoKungFooPos.x(), m_logoKungFooPos.y() - 4.0f),
		 //Vector2(0.0, m_logoKungFooPos.y()), Vector2(0.0f, m_logoKungFooPos.y()),
		 CinematicTimespan(5.8, 6.8)));*/
		m_cinEngine.addTimelineItem(
				std::make_shared < CinematicTranspararencyAnimation
						> ("logo_bar", 0.0f, 1.0f, CinematicTimespan(5.79, 8.8)));

		m_cinEngine.addTimelineItem(
				std::make_shared < CinematicSound > ("player_yell1", CinematicTimepoint(8.2)));
		m_cinEngine.addTimelineItem(
				std::make_shared < CinematicLambda > (lmdNextStage, CinematicTimepoint(12.0)));
	} else {
		// intro done, move on with your life ...
		StateChangeInfoPtr pChange(new GameToMenuInfo());
		gs.requestStateChange("menu", pChange);
	}
}

