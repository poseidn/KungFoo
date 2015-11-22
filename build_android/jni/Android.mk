# Copyright (C) 2010 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

LOCAL_PATH := $(call my-dir)
ADD_INCLUDES := $(LOCAL_PATH)/../external/ $(LOCAL_PATH)/../../src/ \
	../src/DescentEngine/external/tinyxml2/ \
	../src/DescentEngine/external/ \
	../src/DescentEngine/external/bullet \
	../src/DescentEngine/external/lua \
	../src/DescentEngine/external/luabind

DESCENT_DEFINES := -DDESCENT_LOG_ENABLED -DLUA_ANSI -DUSE_ANDROID_OPENGL -DUSE_ANDROID -DUSE_THREADING_NULL

#enable for debug builds
#DESCENT_DEFINES := $(DESCENT_DEFINES) -DGL_CHECK_ERROR_ENABLED -DDESCENT_PROFILE
# for release compiles
DESCENT_DEFINES := $(DESCENT_DEFINES)
## don't show all the warnings, otherwise the compiler will go crazy with boost
#DESCENT_CPP_FLAGS := -std=c++11 -Wfatal-errors -Wall -Wno-unused-variable -Wno-variadic-macros -Ofast $(DESCENT_DEFINES) 

## use clang to build
## disabled for now, clang still has problems with c++11 chrono
#NDK_TOOLCHAIN_VERSION := clang
DESCENT_CPP_FLAGS := -std=c++11 -Wfatal-errors -Wno-literal-suffix -O3 $(DESCENT_DEFINES)

DESCENT_SRC_PATH := ../../src/
DESCENT_ENGINE_SRC_PATH := ../../src/DescentEngine/src
DESCENT_ENGINE_EXTERNAL_PATH := ../../src/DescentEngine/external

DESCENT_LOGIC_SRC_PATH := ../../src/DescentLogic/src
DESCENT_GAME_SRC_PATH := ../../src/DescentEngine/src

include $(CLEAR_VARS)

LOCAL_MODULE := DescentEngine

LOCAL_C_INCLUDES := $(ADD_INCLUDES)
LOCAL_CPPFLAGS := $(DESCENT_CPP_FLAGS)
LOCAL_CPP_FEATURES := rtti exceptions
# so we can use the android_app struct also here 
LOCAL_STATIC_LIBRARIES := android_native_app_glue


LOCAL_SRC_FILES := $(DESCENT_ENGINE_EXTERNAL_PATH)/tinyxml2/tinyxml2.cpp \
					$(DESCENT_ENGINE_EXTERNAL_PATH)/Box2D/Common/b2BlockAllocator.cpp \
					$(DESCENT_ENGINE_EXTERNAL_PATH)/Box2D/Common/b2Draw.cpp \
					$(DESCENT_ENGINE_EXTERNAL_PATH)/Box2D/Common/b2Math.cpp \
					$(DESCENT_ENGINE_EXTERNAL_PATH)/Box2D/Common/b2Settings.cpp \
					$(DESCENT_ENGINE_EXTERNAL_PATH)/Box2D/Common/b2StackAllocator.cpp \
					$(DESCENT_ENGINE_EXTERNAL_PATH)/Box2D/Common/b2Timer.cpp \
					$(DESCENT_ENGINE_EXTERNAL_PATH)/Box2D/Dynamics/Joints/b2DistanceJoint.cpp \
					$(DESCENT_ENGINE_EXTERNAL_PATH)/Box2D/Dynamics/Joints/b2FrictionJoint.cpp \
					$(DESCENT_ENGINE_EXTERNAL_PATH)/Box2D/Dynamics/Joints/b2GearJoint.cpp \
					$(DESCENT_ENGINE_EXTERNAL_PATH)/Box2D/Dynamics/Joints/b2Joint.cpp \
					$(DESCENT_ENGINE_EXTERNAL_PATH)/Box2D/Dynamics/Joints/b2MotorJoint.cpp \
					$(DESCENT_ENGINE_EXTERNAL_PATH)/Box2D/Dynamics/Joints/b2MouseJoint.cpp \
					$(DESCENT_ENGINE_EXTERNAL_PATH)/Box2D/Dynamics/Joints/b2PrismaticJoint.cpp \
					$(DESCENT_ENGINE_EXTERNAL_PATH)/Box2D/Dynamics/Joints/b2PulleyJoint.cpp \
					$(DESCENT_ENGINE_EXTERNAL_PATH)/Box2D/Dynamics/Joints/b2RevoluteJoint.cpp \
					$(DESCENT_ENGINE_EXTERNAL_PATH)/Box2D/Dynamics/Joints/b2RopeJoint.cpp \
					$(DESCENT_ENGINE_EXTERNAL_PATH)/Box2D/Dynamics/Joints/b2WeldJoint.cpp \
					$(DESCENT_ENGINE_EXTERNAL_PATH)/Box2D/Dynamics/Joints/b2WheelJoint.cpp \
					$(DESCENT_ENGINE_EXTERNAL_PATH)/Box2D/Dynamics/Contacts/b2CircleContact.cpp \
					$(DESCENT_ENGINE_EXTERNAL_PATH)/Box2D/Dynamics/Contacts/b2Contact.cpp \
					$(DESCENT_ENGINE_EXTERNAL_PATH)/Box2D/Dynamics/Contacts/b2ContactSolver.cpp \
					$(DESCENT_ENGINE_EXTERNAL_PATH)/Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.cpp \
					$(DESCENT_ENGINE_EXTERNAL_PATH)/Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.cpp \
					$(DESCENT_ENGINE_EXTERNAL_PATH)/Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.cpp \
					$(DESCENT_ENGINE_EXTERNAL_PATH)/Box2D/Dynamics/Contacts/b2ChainAndCircleContact.cpp \
					$(DESCENT_ENGINE_EXTERNAL_PATH)/Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.cpp \
					$(DESCENT_ENGINE_EXTERNAL_PATH)/Box2D/Dynamics/Contacts/b2PolygonContact.cpp \
					$(DESCENT_ENGINE_EXTERNAL_PATH)/Box2D/Dynamics/b2Body.cpp \
					$(DESCENT_ENGINE_EXTERNAL_PATH)/Box2D/Dynamics/b2ContactManager.cpp \
					$(DESCENT_ENGINE_EXTERNAL_PATH)/Box2D/Dynamics/b2Fixture.cpp \
					$(DESCENT_ENGINE_EXTERNAL_PATH)/Box2D/Dynamics/b2Island.cpp \
					$(DESCENT_ENGINE_EXTERNAL_PATH)/Box2D/Dynamics/b2World.cpp \
					$(DESCENT_ENGINE_EXTERNAL_PATH)/Box2D/Dynamics/b2WorldCallbacks.cpp \
					$(DESCENT_ENGINE_EXTERNAL_PATH)/Box2D/Collision/Shapes/b2CircleShape.cpp \
					$(DESCENT_ENGINE_EXTERNAL_PATH)/Box2D/Collision/Shapes/b2EdgeShape.cpp \
					$(DESCENT_ENGINE_EXTERNAL_PATH)/Box2D/Collision/Shapes/b2ChainShape.cpp \
					$(DESCENT_ENGINE_EXTERNAL_PATH)/Box2D/Collision/Shapes/b2PolygonShape.cpp \
					$(DESCENT_ENGINE_EXTERNAL_PATH)/Box2D/Collision/b2BroadPhase.cpp \
					$(DESCENT_ENGINE_EXTERNAL_PATH)/Box2D/Collision/b2CollideCircle.cpp \
					$(DESCENT_ENGINE_EXTERNAL_PATH)/Box2D/Collision/b2CollideEdge.cpp \
					$(DESCENT_ENGINE_EXTERNAL_PATH)/Box2D/Collision/b2CollidePolygon.cpp \
					$(DESCENT_ENGINE_EXTERNAL_PATH)/Box2D/Collision/b2Collision.cpp \
					$(DESCENT_ENGINE_EXTERNAL_PATH)/Box2D/Collision/b2Distance.cpp \
					$(DESCENT_ENGINE_EXTERNAL_PATH)/Box2D/Collision/b2DynamicTree.cpp \
					$(DESCENT_ENGINE_EXTERNAL_PATH)/Box2D/Collision/b2TimeOfImpact.cpp \
					$(DESCENT_ENGINE_SRC_PATH)/Log.cpp \
					$(DESCENT_ENGINE_SRC_PATH)/Engines.cpp \
					$(DESCENT_ENGINE_SRC_PATH)/ScriptEngine/ScriptEngine.cpp \
					$(DESCENT_ENGINE_SRC_PATH)/RenderEngine.cpp \
					$(DESCENT_ENGINE_SRC_PATH)/Texture.cpp \
					$(DESCENT_ENGINE_SRC_PATH)/GameLoop.cpp \
					$(DESCENT_ENGINE_SRC_PATH)/Physics/PhysicsEngineBox2D.cpp \
					$(DESCENT_ENGINE_SRC_PATH)/Physics/CollisionGroups.cpp \
					$(DESCENT_ENGINE_SRC_PATH)/Android_OpenGL/AndroidOpenGLESInterface.cpp \
					$(DESCENT_ENGINE_SRC_PATH)/Common_OpenGL/OpenGL_ES_Render.cpp \
					$(DESCENT_ENGINE_SRC_PATH)/CinematicEngine/CinematicEngine.cpp \
					$(DESCENT_ENGINE_SRC_PATH)/Visuals/SpriteVisual.cpp \
					$(DESCENT_ENGINE_SRC_PATH)/Visuals/ParticleSystemVisual.cpp \
					$(DESCENT_ENGINE_SRC_PATH)/Visuals/TextVisual.cpp \
					$(DESCENT_ENGINE_SRC_PATH)/Pathfinding/Pathfinding.cpp \
					$(DESCENT_ENGINE_SRC_PATH)/EntityEngine/EntityEngine.cpp \
					$(DESCENT_ENGINE_SRC_PATH)/EntityEngine/EntityTemplate.cpp \
					$(DESCENT_ENGINE_SRC_PATH)/EntityEngine/Entity.cpp \
					$(DESCENT_ENGINE_SRC_PATH)/EntityEngine/MultiVisualEntity.cpp \
					$(DESCENT_ENGINE_SRC_PATH)/Input/AndroidInput.cpp \
					$(DESCENT_ENGINE_SRC_PATH)/Input/InputContainer.cpp \
					$(DESCENT_ENGINE_SRC_PATH)/ResourceEngine/ResourceEngine.cpp \
					$(DESCENT_ENGINE_SRC_PATH)/ResourceEngine/ResourceEngineAndroid.cpp \
					$(DESCENT_ENGINE_SRC_PATH)/AnimationEngine/AnimationEngine.cpp \
					$(DESCENT_ENGINE_SRC_PATH)/AnimationEngine/ParticleAnimation.cpp \
					$(DESCENT_ENGINE_SRC_PATH)/AnimationEngine/TextAnimation.cpp \
					$(DESCENT_ENGINE_SRC_PATH)/AnimationEngine/EntityAnimation.cpp \
					$(DESCENT_ENGINE_SRC_PATH)/Performance/SectionTimer.cpp

include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE := DescentLogic

LOCAL_C_INCLUDES := $(ADD_INCLUDES)
LOCAL_CPPFLAGS := $(DESCENT_CPP_FLAGS)
LOCAL_CPP_FEATURES := rtti exceptions
# so we can use the android_app struct also here 
LOCAL_STATIC_LIBRARIES := android_native_app_glue DescentEngine

LOCAL_SRC_FILES := 	$(DESCENT_LOGIC_SRC_PATH)/Game/GameState.cpp \
					$(DESCENT_LOGIC_SRC_PATH)/Menu/MenuState.cpp \
					$(DESCENT_LOGIC_SRC_PATH)/LevelFactory.cpp \
					$(DESCENT_LOGIC_SRC_PATH)/Entities/GameTemplates.cpp \
					$(DESCENT_LOGIC_SRC_PATH)/Entities/FighterEntity.cpp \
					$(DESCENT_LOGIC_SRC_PATH)/Common/Aspects/QuitAspect.cpp \
					$(DESCENT_LOGIC_SRC_PATH)/Config/GameRules.cpp \
					$(DESCENT_LOGIC_SRC_PATH)/Config/PlayerMovement.cpp \
					$(DESCENT_LOGIC_SRC_PATH)/Config/EnemyBehaviour.cpp \
					$(DESCENT_LOGIC_SRC_PATH)/Config/GameMovement.cpp \
					$(DESCENT_LOGIC_SRC_PATH)/Game/Aspects/MovePlayerAspect.cpp \
					$(DESCENT_LOGIC_SRC_PATH)/Game/Aspects/AttackAspect.cpp \
					$(DESCENT_LOGIC_SRC_PATH)/Game/Aspects/ExecuteMoveIntentsAspect.cpp \
					$(DESCENT_LOGIC_SRC_PATH)/Game/Aspects/ForwardScrollingAspect.cpp \
					$(DESCENT_LOGIC_SRC_PATH)/Game/Aspects/FreeScrollingAspect.cpp \
					$(DESCENT_LOGIC_SRC_PATH)/Game/Aspects/StatusAspect.cpp \
					$(DESCENT_LOGIC_SRC_PATH)/Game/Aspects/EnemyAIAspect.cpp \
					$(DESCENT_LOGIC_SRC_PATH)/Game/Aspects/DieAspect.cpp \
					$(DESCENT_LOGIC_SRC_PATH)/Game/Aspects/StartGameAspect.cpp \
					$(DESCENT_LOGIC_SRC_PATH)/Game/Aspects/SpecialMoveDetectionAspect.cpp \
					$(DESCENT_LOGIC_SRC_PATH)/Game/Aspects/ScoringAspect.cpp \
					$(DESCENT_LOGIC_SRC_PATH)/Game/Aspects/ComboDetectionAspect.cpp \
					$(DESCENT_LOGIC_SRC_PATH)/Game/Aspects/DisplayEventsAspect.cpp \
					$(DESCENT_LOGIC_SRC_PATH)/Game/Aspects/RemoveEntitiesAspect.cpp \
					$(DESCENT_LOGIC_SRC_PATH)/Game/Aspects/LevelEditorAspect.cpp \
					$(DESCENT_LOGIC_SRC_PATH)/Intro/Aspects/AdvanceIntroAspect.cpp \
					$(DESCENT_LOGIC_SRC_PATH)/Intro/Aspects/InputIntroAspect.cpp \
					$(DESCENT_LOGIC_SRC_PATH)/Menu/Aspects/InputMenuAspect.cpp \
					$(DESCENT_LOGIC_SRC_PATH)/Menu/Aspects/NavigateMenuAspect.cpp \
					$(DESCENT_LOGIC_SRC_PATH)/Menu/Aspects/StartMenuAspect.cpp 

include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_C_INCLUDES := $(ADD_INCLUDES)
LOCAL_MODULE    := FastDescentNativeActivity
LOCAL_CPPFLAGS := $(DESCENT_CPP_FLAGS)
LOCAL_SRC_FILES := android_main.cpp
LOCAL_LDLIBS    := -llog -landroid -lGLESv1_CM
LOCAL_STATIC_LIBRARIES := cpufeatures android_native_app_glue ndk_helper DescentEngine DescentLogic

include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/ndk_helper)
$(call import-module,android/native_app_glue)
$(call import-module,android/cpufeatures)