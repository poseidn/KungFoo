cmake_minimum_required (VERSION 2.6)
project (Descent)

include_directories( ${Descent_SOURCE_DIR}/src )
include ( ../CMake_Externals.txt )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DBT_NO_PROFILE=1" )

set(OPTIONAL_CPP "")

if (UNIX)
	set(OPTIONAL_CPP "external/inotify-cxx/inotify-cxx.cpp")
endif()

add_library(DescentEngine STATIC #SHARED
	${OPTIONAL_CPP}
	external/tinyxml2/tinyxml2.cpp

	src/VectorTypes.cpp
	src/Log.cpp
	src/Engines.cpp
	src/RenderEngine.cpp
	src/GameLoop.cpp
	src/Texture.cpp
	
	src/Performance/SectionTimer.cpp
	
	src/Pathfinding/Pathfinding.cpp
	
	src/ResourceEngine/ResourceEngine.cpp
	src/ResourceEngine/ResourceEngineSDL.cpp
	
	src/SoundEngine/SoundEngineSDL.cpp
	src/Physics/PhysicsEngineBox2D.cpp
	src/Physics/CollisionGroups.cpp
	
	src/Input/SDLInput.cpp
	src/Input/InputContainer.cpp
	
	src/SDL_OpenGL/SDLOpenGLInterface.cpp
	src/Common_OpenGL/OpenGL_ES_Render.cpp
	
	src/Visuals/SpriteVisual.cpp
	src/Visuals/ParticleSystemVisual.cpp
	src/Visuals/TextVisual.cpp
	
	src/EntityEngine/EntityEngine.cpp
	src/EntityEngine/Entity.cpp
	src/EntityEngine/EntityTemplate.cpp
	src/EntityEngine/MultiVisualEntity.cpp

	src/AnimationEngine/AnimationEngine.cpp
	src/AnimationEngine/EntityAnimation.cpp
	src/AnimationEngine/ParticleAnimation.cpp
	src/AnimationEngine/TextAnimation.cpp
	
	src/CinematicEngine/CinematicEngine.cpp

	src/ScriptEngine/ScriptEngine.cpp
		
	external/Box2D/Common/b2BlockAllocator.cpp
	external/Box2D/Common/b2Draw.cpp
	external/Box2D/Common/b2Math.cpp
	external/Box2D/Common/b2Settings.cpp
	external/Box2D/Common/b2StackAllocator.cpp
	external/Box2D/Common/b2Timer.cpp
	
	external/Box2D/Dynamics/Joints/b2DistanceJoint.cpp
	external/Box2D/Dynamics/Joints/b2FrictionJoint.cpp
	external/Box2D/Dynamics/Joints/b2GearJoint.cpp
	external/Box2D/Dynamics/Joints/b2Joint.cpp
	external/Box2D/Dynamics/Joints/b2MotorJoint.cpp
	external/Box2D/Dynamics/Joints/b2MouseJoint.cpp
	external/Box2D/Dynamics/Joints/b2PrismaticJoint.cpp
	external/Box2D/Dynamics/Joints/b2PulleyJoint.cpp
	external/Box2D/Dynamics/Joints/b2RevoluteJoint.cpp
	external/Box2D/Dynamics/Joints/b2RopeJoint.cpp
	external/Box2D/Dynamics/Joints/b2WeldJoint.cpp
	external/Box2D/Dynamics/Joints/b2WheelJoint.cpp
	
	external/Box2D/Dynamics/Contacts/b2CircleContact.cpp
	external/Box2D/Dynamics/Contacts/b2Contact.cpp
	external/Box2D/Dynamics/Contacts/b2ContactSolver.cpp
	external/Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.cpp
	external/Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.cpp
	external/Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.cpp
	external/Box2D/Dynamics/Contacts/b2ChainAndCircleContact.cpp
	external/Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.cpp
	external/Box2D/Dynamics/Contacts/b2PolygonContact.cpp
	
	external/Box2D/Dynamics/b2Body.cpp
	external/Box2D/Dynamics/b2ContactManager.cpp
	external/Box2D/Dynamics/b2Fixture.cpp
	external/Box2D/Dynamics/b2Island.cpp
	external/Box2D/Dynamics/b2World.cpp
	external/Box2D/Dynamics/b2WorldCallbacks.cpp
	
	external/Box2D/Collision/Shapes/b2CircleShape.cpp
	external/Box2D/Collision/Shapes/b2EdgeShape.cpp
	external/Box2D/Collision/Shapes/b2ChainShape.cpp
	external/Box2D/Collision/Shapes/b2PolygonShape.cpp
	
	external/Box2D/Collision/b2BroadPhase.cpp
	external/Box2D/Collision/b2CollideCircle.cpp
	external/Box2D/Collision/b2CollideEdge.cpp
	external/Box2D/Collision/b2CollidePolygon.cpp
	external/Box2D/Collision/b2Collision.cpp
	external/Box2D/Collision/b2Distance.cpp
	external/Box2D/Collision/b2DynamicTree.cpp
	external/Box2D/Collision/b2TimeOfImpact.cpp
)

target_link_libraries( DescentEngine SDL SDL_image SDL_mixer )

if(UNIX)
	target_link_libraries( DescentEngine GL )
endif()

if(WIN32)
	target_link_libraries( DescentEngine opengl32 )
endif()
 

