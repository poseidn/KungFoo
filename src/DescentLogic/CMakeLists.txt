cmake_minimum_required (VERSION 2.6)
project (Descent)

include_directories( ${Descent_SOURCE_DIR}/src ) 
include_directories( ${Descent_SOURCE_DIR}/.. )

include ( ../CMake_Externals.txt )

add_library(DescentLogic
	src/Game/GameState.cpp
	src/Menu/MenuState.cpp
	
	src/LevelFactory.cpp
	
	src/Config/GameRules.cpp
	src/Config/EnemyBehaviour.cpp
	src/Config/PlayerMovement.cpp
	src/Config/GameMovement.cpp

	# aspects
	src/Common/Aspects/QuitAspect.cpp
	src/Common/Aspects/DebugFunctionAspect.cpp
	
	src/Game/Aspects/StatusAspect.cpp
	src/Game/Aspects/AttackAspect.cpp
	src/Game/Aspects/MovePlayerAspect.cpp
	src/Game/Aspects/ExecuteMoveIntentsAspect.cpp
	src/Game/Aspects/ForwardScrollingAspect.cpp
	src/Game/Aspects/FreeScrollingAspect.cpp
	src/Game/Aspects/DieAspect.cpp
	src/Game/Aspects/EnemyAIAspect.cpp
	src/Game/Aspects/InputTranslationAspect.cpp
	src/Game/Aspects/SpecialMoveDetectionAspect.cpp
	src/Game/Aspects/StartGameAspect.cpp
	src/Game/Aspects/ScoringAspect.cpp
	src/Game/Aspects/ComboDetectionAspect.cpp
	src/Game/Aspects/DisplayEventsAspect.cpp
	src/Game/Aspects/RemoveEntitiesAspect.cpp
	src/Game/Aspects/LevelEditorAspect.cpp
	
	src/Menu/Aspects/StartMenuAspect.cpp	
	src/Menu/Aspects/NavigateMenuAspect.cpp	
	src/Menu/Aspects/InputMenuAspect.cpp	

	src/Intro/Aspects/InputIntroAspect.cpp	
	src/Intro/Aspects/AdvanceIntroAspect.cpp	
	 
	src/Entities/GameTemplates.cpp
	src/Entities/FighterEntity.cpp

	src/Tools/DelayedInput.cpp
)

target_link_libraries( DescentLogic DescentEngine )

