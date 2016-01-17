/*
Copyright (C) 2016 Thomas Hauth. All Rights Reserved.
* Written by Thomas Hauth (Thomas.Hauth@web.de)

This file is part of Kung Foo Barracuda.

Kung Foo Barracuda is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Kung Foo Barracuda is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Kung Foo Barracuda.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <memory>

#include <DescentEngine/src/Log.h>
#include <DescentEngine/src/Engines.h>
#include <DescentEngine/src/Rectangle.h>

#include <DescentEngine/src/StateEngine/StateTransitions.h>
#include <DescentEngine/src/Physics/PhysicsEngine.h>

#include <DescentEngine/src/ResourceEngine/ResourceEngine.h>

#include <DescentEngine/src/GameLoop.h>
#include <DescentEngine/src/EntityEngine/Entity.h>
#include <DescentEngine/src/EntityEngine/EntityFactory.h>
#include <DescentEngine/src/RandomEngine.h>
#include <DescentEngine/src/ScriptEngine/ScriptEngine.h>

#include <DescentEngine/src/SoundEngine/SoundEngine.h>

#include <DescentEngine/src/CinematicEngine/CinematicEngine.h>
#include <DescentEngine/src/CinematicEngine/CinematicAspect.h>

#include <DescentEngine/src/Visuals/SpriteVisual.h>
#include <DescentEngine/src/Visuals/ParticleSystemVisual.h>
#include <DescentEngine/src/Input/InputSystem.h>

#include <DescentEngine/src/AnimationEngine/ParticleAnimation.h>

// states
#include <DescentLogic/src/Game/GameState.h>
#include <DescentLogic/src/Menu/MenuState.h>
#include <DescentLogic/src/Intro/IntroState.h>

// include all needed aspects
#include <DescentLogic/src/Common/Aspects/QuitAspect.h>
#include <DescentLogic/src/Common/Aspects/DebugFunctionAspect.h>
#include <DescentLogic/src/Common/Aspects/ScriptAspect.h>

#include <DescentLogic/src/Game/Aspects/StatusAspect.h>
#include <DescentLogic/src/Game/Aspects/AttackAspect.h>
#include <DescentLogic/src/Game/Aspects/MovePlayerAspect.h>
#include <DescentLogic/src/Game/Aspects/ExecuteMoveIntentsAspect.h>
#include <DescentLogic/src/Game/Aspects/ForwardScrollingAspect.h>
#include <DescentLogic/src/Game/Aspects/DieAspect.h>
#include <DescentLogic/src/Game/Aspects/FreeScrollingAspect.h>
#include <DescentLogic/src/Game/Aspects/StartGameAspect.h>
#include <DescentLogic/src/Game/Aspects/EnemyAIAspect.h>
#include <DescentLogic/src/Game/Aspects/DebugVisualCollisionsAspect.h>
#include <DescentLogic/src/Game/Aspects/SpecialMoveDetectionAspect.h>
#include <DescentLogic/src/Game/Aspects/ScoringAspect.h>
#include <DescentLogic/src/Game/Aspects/ComboDetectionAspect.h>
#include <DescentLogic/src/Game/Aspects/DisplayEventsAspect.h>
#include <DescentLogic/src/Game/Aspects/RemoveEntitiesAspect.h>
#include <DescentLogic/src/Game/Aspects/LevelEditorAspect.h>

#include <DescentLogic/src/Menu/Aspects/StartMenuAspect.h>
#include <DescentLogic/src/Menu/Aspects/NavigateMenuAspect.h>
#include <DescentLogic/src/Menu/Aspects/InputMenuAspect.h>
#include <DescentLogic/src/Menu/Aspects/DebugRenderAspect.h>

#include <DescentLogic/src/Intro/Aspects/InputIntroAspect.h>
#include <DescentLogic/src/Intro/Aspects/AdvanceIntroAspect.h>

#include <DescentLogic/src/Game/Aspects/InputTranslationAspect.h>

#include <DescentLogic/src/LevelFactory.h>

#include <DescentLogic/src/Entities/PlayerEntity.h>
#include <DescentLogic/src/Entities/TextureIds.h>
#include <DescentLogic/src/Entities/GameTemplates.h>

struct DescentFrameworkBase: boost::noncopyable {

#ifdef USE_SDL
	SDLInput * m_hardwareInput = nullptr;
#endif

#ifdef USE_ANDROID
	AndroidInput * m_hardwareInput = nullptr;
#endif

	DescentFrameworkBase(bool asLevelEditor = false, bool demoMode = false,
			bool muted = false, bool forwardScrool = true,
			bool withIntro = true, bool showFps = false, bool profile = false,
			std::string profileFileName = "") :
			m_asLevelEditor(asLevelEditor), m_demoMode(demoMode), m_muted(
					muted), m_forwardScroll(forwardScrool), m_withIntro(
					withIntro), m_showFps(showFps), m_profile(profile), m_profileFileName(
					profileFileName) {

		m_snd.setMuted(m_muted);

		m_delayInput = std14::make_unique<DelayedInput>();

		// todo memleak
#ifdef USE_SDL
		m_hardwareInput = new SDLInput();
		m_input.reset(new InputSystem( m_hardwareInput, m_delayInput.get()));
#endif

#ifdef USE_ANDROID
		m_hardwareInput = nullptr;
		m_input.reset(new InputSystem());

		// only single player for android atm
		m_input->assignPlayerToInput(0,0);
#endif

	}

	~DescentFrameworkBase() {
		m_resources.freeResources();
	}

	void initialize() {

		GameTemplates::registerTemplates(m_ee);

#ifdef USE_SDL
		// general SDL init
		if (SDL_Init(SDL_INIT_EVENTTHREAD) < 0)
		{

			fprintf(stderr, "Video initialization failed: %s\n",
					SDL_GetError());
			exit(1);
		}
#endif
	}
	/*
	 * needs to be fixed in android build
	 * probably use glXMakeContextCurrent in the render thread*/
	void initRenderEngine(
			RenderEngine::interface_type::InterfaceDataType & co) {
		m_re.init(co);

		// can only do this, one the graphics backend is available
		if (m_virtualControls)
			enableVirtualControls();
	}

	void releaseRenderEngine() {
		m_re.release();
	}

	bool isRenderEngineReady() {
		return m_re.isInitialized();
	}

	// can be called to pause the game. Atm this only
	// pauses the sound playback
	void pauseGame() {
		m_snd.pauseSound();
	}

	void resumeGame() {
		m_snd.resumeSound();

	}

	void executeBase() {
		logging::resetLogFile();

		logging::Info() << "Starting framework";

		initialize();
		m_engines.reset(
				new Engines(m_re, m_resources, m_an, m_ee, m_snd, m_rand,
						*(m_input.get()), m_physics, *(m_script.get())));

		logging::Info() << "GameState created";
		m_gameState.reset(new GameState(*m_engines));

		if (m_asLevelEditor) {
			m_gameState->m_levelName = m_levelName;
		}

		if (m_demoMode) {

			float delayFactor = 1.0f;
			float gameStartOffset = 0.0f;

			m_delayInput->addCommand(
					DelayedInput::InputCommand(
							DelayedInput::InputCommand::ActionEnum::Kick,
							delayFactor * (1.0f + gameStartOffset)));

			m_delayInput->addCommand(
					DelayedInput::InputCommand(
							DelayedInput::InputCommand::ActionEnum::Jump,
							delayFactor * (2.0f + gameStartOffset)));

			m_delayInput->addCommand(
					DelayedInput::InputCommand(
							DelayedInput::InputCommand::ActionEnum::Kick,
							delayFactor * (5.0f + gameStartOffset)));
			m_delayInput->addCommand(
					DelayedInput::InputCommand(
							DelayedInput::InputCommand::ActionEnum::Kick,
							delayFactor * (5.5f + gameStartOffset)));
			m_delayInput->addCommand(
					DelayedInput::InputCommand(
							DelayedInput::InputCommand::ActionEnum::Kick,
							delayFactor * (6.4f + gameStartOffset)));

			m_delayInput->addCommand(
					DelayedInput::InputCommand(
							DelayedInput::InputCommand::ActionEnum::Jump,
							delayFactor * (7.0f + gameStartOffset)));
			m_delayInput->addCommand(
					DelayedInput::InputCommand(
							DelayedInput::InputCommand::ActionEnum::Kick,
							delayFactor * (8.0f + gameStartOffset)));

			m_delayInput->addCommand(
					DelayedInput::InputCommand(
							DelayedInput::InputCommand::ActionEnum::Exit,
							delayFactor * (15.0f + gameStartOffset)));
		}

		m_cinema.reset(new CinematicEngine(*m_engines));

		m_introState.reset(new IntroState(*m_engines));
		StateEngine<IntroState> * introEngine = new StateEngine<IntroState>(
				*m_introState);
		introEngine->registerAspect(new InputIntroAspect<IntroState>());
		introEngine->registerAspect(new AdvanceIntroAspect(*m_cinema));
		introEngine->registerAspect(
				new CinematicAspect<IntroState, CinematicEngine>(*m_cinema));
		introEngine->registerAspect(new DebugFunctionAspect<IntroState>());

		if (m_withIntro && (!m_asLevelEditor)) {
			m_strans.addState("intro", introEngine);
		}

		m_menuState.reset(new MenuState(*m_engines));
		StateEngine<MenuState> * menuEngine = new StateEngine<MenuState>(
				*m_menuState);
		/*m_script->addObjectRegister([](lua_State * luaState)
		 {
		 luabind::module (luaState)[
		 //
		 luabind::class_<MenuState>("MenuState")];
		 });*/

		menuEngine->registerAspect(new InputMenuAspect<MenuState>());
		menuEngine->registerAspect(new QuitAspect<MenuState>());

		const bool renderDebug = false;
		if (renderDebug) {
			menuEngine->registerAspect(new DebugRenderAspect());
		} else {
			menuEngine->registerAspect(new NavigateMenuAspect());
			menuEngine->registerAspect(new StartMenuAspect());
			menuEngine->registerAspect(new DebugFunctionAspect<MenuState>());
			//menuEngine->registerAspect(new ScriptAspect<MenuState>("boot_env", { ScriptImplements::Step }));
		}

		if (!m_asLevelEditor)
			m_strans.addState("menu", menuEngine);

		StateEngine<GameState> * stateEngine = new StateEngine<GameState>(
				*m_gameState);
		/*
		 m_script->addObjectRegister([](lua_State * luaState)
		 {
		 luabind::module(luaState)[
		 luabind::class_<GameState>("GameState")
		 //
		 //.def(luabind::constructor<>())
		 //
		 .def("getTotalScore", &GameState::getTotalScore )
		 //
		 .def("getTextScore", &GameState::getTextScore )
		 // .def("Fatal", &LuaLogging::Fatal)
		 ];
		 });*/
		stateEngine->registerAspect(new RemoveEntitiesAspect());
		stateEngine->registerAspect(new InputTranslationAspect<GameState>());
		stateEngine->registerAspect(new StatusAspect());
		stateEngine->registerAspect(new MovePlayerAspect(m_forwardScroll));
		stateEngine->registerAspect(new EnemyAIAspect());
		stateEngine->registerAspect(
				new ForwardScrollingAspect(m_forwardScroll));
		stateEngine->registerAspect(new ScoringAspect());
		stateEngine->registerAspect(new StartGameAspect());
		stateEngine->registerAspect(new ComboDetectionAspect());
		stateEngine->registerAspect(new DisplayEventsAspect());
		stateEngine->registerAspect(new DebugFunctionAspect<GameState>());
		/*stateEngine->registerAspect(new ScriptAspect<GameState>("praise_score_increase", { {
		 ScriptImplements::Step, ScriptImplements::OnScoreIncrease } }));*/
		//stateEngine->registerAspect(new DebugVisualCollisionsAspect());
		if (m_asLevelEditor) {

		}

		// must be done, after the movement intentions are complete
		// the move intents will be excuted by the game loop, after all the aspects
		// have been proceesed
		stateEngine->registerAspect(new QuitAspect<GameState>());
		stateEngine->registerAspect(new AttackAspect());
		stateEngine->registerAspect(new DieAspect());
		//stateEngine->registerAspect(new DebugVisualCollisionsAspect());

		stateEngine->registerAspect(new SpecialMoveDetectionAspect());

		if (!m_asLevelEditor) {
			m_strans.addState("game", stateEngine);
		}

		if (m_asLevelEditor) {
			m_levelState.reset(new GameState(*m_engines));

			StateEngine<GameState> * levelEngine = new StateEngine<GameState>(
					*m_levelState);

			levelEngine->registerAspect(
					new InputTranslationAspect<GameState>());
			levelEngine->registerAspect(new FreeScrollingAspect());
			levelEngine->registerAspect(new QuitAspect<GameState>());
			levelEngine->registerAspect(new LevelEditorAspect(m_levelName));

			m_strans.addState("lvl_edit", levelEngine);

			m_input->assignPlayerToInput(0, 0);
		}

		m_gameLoop.reset(
				new GameLoop(m_re, m_strans, m_ee, m_an, getInputSystem(),
						m_physics, m_showFps, m_profile, m_profileFileName));

		//m_gl->setInitialContentFunc(initialContentFunc);

		logging::Info() << "Aspects registered";

		/*		auto texDpad = m_resources.loadImage("dpad1");
		 SpriteVisual svDpad(m_re.getScreenTransform(), texDpad, Vector2(4.0f, 4.0f), Vector2::Unit(),
		 LayerPriorityTopMost);
		 svDpad.setIngame( m_re.getScreenTransform(), Vector2(4.0f, 4.0f), false );
		 m_re.addSpriteVisual(svDpad);*/
		// get the music going
		//auto music1 = m_resources.loadMusic("musik1");
		//m_snd.playMusic(music1);
		logging::Info() << "Engines and Aspects initialized";

		m_isInitialized = true;
	}

	bool isInitialized() const {
		return m_isInitialized;
	}

	void setVirtualControls() {
		m_virtualControls = true;
	}

	ResourceEngine & getResourceEngine() {
		return m_resources;
	}

	RenderEngine & getRenderEngine() {
		return m_re;
	}

	InputSystem & getInputSystem() {
		return *m_input.get();
	}

	SoundEngine & getSoundEngine() {
		return m_snd;
	}

	GameState * getGameState() {
		return m_gameState.get();
	}

	std::string m_levelName;

protected:

	RenderEngine m_re;
	//std::unique_ptr<GameLoop> m_gl;
	// todo: do the dest calls correctly and call SDL_quit afterwards
	std::unique_ptr<GameLoop> m_gameLoop;
	AnimationEngine m_an;
	ResourceEngine m_resources;
	EntityEngine m_ee;
	std::unique_ptr<InputSystem> m_input;
	StateTransitions m_strans;
	SoundEngine m_snd;
	RandomEngine m_rand;
	PhysicsEngine m_physics;

	//InputEgine * m_sdlInput;
	std::unique_ptr<DelayedInput> m_delayInput;

	std::unique_ptr<Engines> m_engines;
	std::unique_ptr<GameState> m_gameState;
	std::unique_ptr<GameState> m_levelState;
	std::unique_ptr<MenuState> m_menuState;
	std::unique_ptr<IntroState> m_introState;
	std::unique_ptr<NullState> m_nullState;
	std::unique_ptr<CinematicEngine> m_cinema;
	std::unique_ptr<ScriptEngine> m_script;
	bool m_asLevelEditor;
	bool m_demoMode;
	bool m_muted;
	bool m_forwardScroll;
	bool m_withIntro;
	bool m_showFps;
	bool m_virtualControls = false;
	bool m_isInitialized = false;
	bool m_profile;
	std::string m_profileFileName;

private:
	void enableVirtualControls() {

#ifdef USE_ANDROID
		EntityFactory fact(*m_engines);

		Vector2 sizeTiles = m_re.getScreenTransform().screenSizeInTiles();
		m_input->setScreenTransform (m_re.getScreenTransform());

		auto posDpad = m_input->getDpadPosition();
		auto posButton1 = m_input->getButton1Position();
		auto posButton2 = m_input->getButton2Position();

		auto dpadEnt = fact.createFromTemplateName<SingleVisualEntity>("dpad1", posDpad);
		dpadEnt->getActiveVisual().get().setIngame(m_re.getScreenTransform(), posDpad, false);
		m_input->addVirtualControlEntity(dpadEnt.get());
		m_ee.addEntity(std::move(dpadEnt));

		auto button1 = fact.createFromTemplateName<SingleVisualEntity>("vbutton1", posButton1);
		button1->getActiveVisual().get().setIngame(m_re.getScreenTransform(), posButton1, false);
		m_input->addVirtualControlEntity(button1.get());
		m_ee.addEntity(std::move(button1));

		auto button2 = fact.createFromTemplateName<SingleVisualEntity>("vbutton2", posButton2);
		button2->getActiveVisual().get().setIngame(m_re.getScreenTransform(), posButton2, false);
		m_input->addVirtualControlEntity(button2.get());
		m_ee.addEntity(std::move(button2));

		// this also means, that we will not show any of the default control selections
		m_menuState->setDeviceItemVisible(false);

#endif

	}

}
;

#ifdef USE_SDL

class DescentFramework: public DescentFrameworkBase
{
public:

	DescentFramework( bool asLevelEditor = false, bool demoMode = false, bool muted = false, bool forwardScrool = true, bool withIntro = true, bool showFps = true, bool profile = false) :
	DescentFrameworkBase ( asLevelEditor, demoMode,muted, forwardScrool, withIntro, showFps, profile, "app_profile.log") {}

	void execute()
	{
		executeBase();
		assert ( m_gameLoop);

		// preload all images, needed for valgrind executes
		// disabled for now ...
		//preloadImages();

		m_gameLoop->run();
	}

};

#endif

#ifdef USE_ANDROID

#include <android_native_app_glue.h>
#include <android/asset_manager.h>
#include <android/native_activity.h>

class AndroidFramework: public DescentFrameworkBase
{
public:
	AndroidFramework( bool profile = false ) : DescentFrameworkBase (
// asLevelEditor
			false,
// demoMode
			false,
// muted
			false,
// forwardScrool
			true,
// withIntro
			true,
// showFps
			false,
// store profile info,
			profile,
// profile file name
			"/storage/sdcard0/app_profile.log")
	{
	}

	void setJavaInterface ( ANativeActivity * native_activity)
	{
		m_javaInterface = std14::make_unique<JavaInterface>( native_activity );
		getResourceEngine().setJavaInterface ( m_javaInterface.get());
		getSoundEngine().setJavaInterface ( m_javaInterface.get());
	}

	// todo : remove
	void androidOnResume () {
		getResourceEngine().reloadAllTextures();
	}

	void freeAllTextures() {
		getResourceEngine().freeAllTextures();
	}

	void setAssetManager( AAssetManager * as) {
		m_resources.setAssetManager(as);
	}

	InputSystem * getInputSystem() {
		return m_input.get();
	}

	void execute()
	{
		executeBase();
	}

	// timeDelta in seconds since last call
	void step ( float timeDelta)
	{
		m_gameLoop->step(timeDelta);
	}

private:
	std::unique_ptr<JavaInterface> m_javaInterface;
};

#endif
