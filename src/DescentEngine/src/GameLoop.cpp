#include "GameLoop.h"

#include <atomic>

#include "Performance/SectionTimer.h"

#include "StateEngine/StateEngine.h"
#include "Pathfinding/Node.h"

#include "StateEngine/StateTransitions.h"
#include "RenderEngine.h"
#include "AnimationEngine/AnimationEngine.h"
#include "EntityEngine/EntityEngine.h"
#include "Input/InputSystem.h"
#include "Physics/PhysicsEngine.h"
#include "Timing.h"

#include "Log.h"

void GameLoop::run() {
	logging::Debug() << "GameLoop::run";

	bool quitApp = false;
	Timing loopTiming;

	if (m_profile) {
		GlobalTimingRepo::Rep.clearFile(m_profileFileName);
	}

	logging::Info() << "Starting game loop";

	float integrateTime = 0.0f;
	float deltaTime = 0.000001f;
	while (true) {
		const float missingTime = m_minTime - deltaTime;
		if (missingTime > 0.0f) {

			// todo: might be a problem because we are not in an SDL loop
			Timing::wait(missingTime);
			deltaTime += missingTime;
		}
		loopTiming.start();
		bool stateChange = step(deltaTime);

		// check if someone wants to exit !
		if (m_stateTransitions.wantsApplicationQuit())
			break;

		if (stateChange)
			deltaTime = m_minTime;
		else
			deltaTime = loopTiming.end();

		if (m_showFps) {
			integrateTime += deltaTime;
			if (integrateTime > 3.0f) {
				integrateTime = 0.0f;
				logging::Info() << "FPS: " << 1.0f / deltaTime;
				logging::Info() << "-> SpriteVisual count " << m_renderEngine.getSpriteVisualActiveCount()
						<< " : " << m_renderEngine.getSpriteVisualCount();
				logging::Info() << "-> Rigid Body all count " << m_physics.getRegisteredEntitiesCount();
				logging::Info() << "-> Rigid Body dynamic count "
						<< m_physics.getRegisteredDynamicsEntitiesCount();
				logging::Info() << " -- entity engine";
				logging::Info() << "-> Navigation node count " << m_entityEngine.getPathfindingNodes().size();
				logging::Info() << "-> Static Entities count " << m_entityEngine.getStaticEntities().size();
				logging::Info() << m_stateTransitions.getDebugState();

			}
		}
	}
}

bool GameLoop::step(float timeDelta) {
	bool stateChange = false;

	if (m_loopIteration > m_profileDumpRate) {
		m_loopIteration = 0;
	} else {
		m_loopIteration++;
	}

	//SectionRepo timingRepo;

	{
		SectionTimer tm(GlobalTimingRepo::Rep, "state");
		stateChange = m_stateTransitions.step(timeDelta);
		if (stateChange) {
			// be sure to not use the (maybe long) wait time
			// which the previous state needed to finish up
			// on the new state
			timeDelta = m_minTime;
		}
	}

// todo: this is only called every five seconds in android ??? wtf ?
	{
		SectionTimer tm(GlobalTimingRepo::Rep, "input");
		m_inputSystem.updateContainer(timeDelta);
	}

// todo: fix anim engine in MT
//m_animationEngine.step(deltaTime);
// get it to seconds

// limit the minimal excution speed
// todo: to this in a smart way for slow machines, also for OpenGL

//if (UseThreading) {

//pthread_mutex_lock(&m_mutexVertexData);

	{
		SectionTimer tm(GlobalTimingRepo::Rep, "animation");
		m_animationEngine.step(timeDelta);
	}

	{
		SectionTimer tm(GlobalTimingRepo::Rep, "physics");
		m_physics.step(timeDelta);
	}

// this is the only critical point between Render thread and logic thread
	//Timing::wait(0.02);
	//m_mutxVertexData.lock();

	{
		SectionTimer tm(GlobalTimingRepo::Rep, "move_int");
		m_entityEngine.executeMoveIntents();
	}

	{
		SectionTimer tm(GlobalTimingRepo::Rep, "update");
		EntityEngine::VisualUpdatePairList visualUpdateList;
// can this be done in a serial q in the render thread ?
		m_entityEngine.updateDirtyEntities(m_renderEngine.getScreenTransform(), visualUpdateList);
	}
	/*
	 for (auto & vUpdate : visualUpdateList) {
	 vUpdate.second(vUpdate.first);
	 }*/

//if (UseThreading) {
	//m_mutxVertexData.unlock();
//pthread_mutex_unlock(&m_mutexVertexData);
//[[}
	{
		SectionTimer tm(GlobalTimingRepo::Rep, "render");
		m_renderEngine.render(timeDelta);
	}

	if (m_profile && (m_loopIteration == 0)) {
		GlobalTimingRepo::Rep.report();
		GlobalTimingRepo::Rep.dumpFile(m_profileFileName);
		GlobalTimingRepo::Rep.clear();
	}

	return stateChange;
}

void GameLoop::render() {
//if (!UseThreading) {
	assert(false);
	//m_renderEngine.render();
//}
}

void GameLoop::initRender() {

//logging::Debug() << "Initializing Renderer";
	RenderEngine::interface_type::InterfaceDataType initData;
	m_renderEngine.init(m_initData);

//m_renderInitialized = true;
//logging::Info() << "Render system initialized";
}

void GameLoop::setInitialContentFunc(std::function<void(void)> f) {
	m_initialContentFunc = f;
}
