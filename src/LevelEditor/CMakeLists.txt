cmake_minimum_required (VERSION 2.6)
project (Descent)

include_directories( ${Descent_SOURCE_DIR}/src ) 
include_directories( ${Descent_SOURCE_DIR}/.. ) 

include ( ../CMake_Externals.txt )

if (UNIX) 
add_executable(LevelEditor
	src/LevelEditorMain.cpp
)
endif()

# use SDL to setup all of our open GL stuff 
add_definitions( -DUSE_SDL_OPENGL )

target_link_libraries( LevelEditor DescentEngine DescentLogic )



