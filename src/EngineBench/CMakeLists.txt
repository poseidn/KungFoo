cmake_minimum_required (VERSION 2.6)
project (Descent)

include_directories( ${Descent_SOURCE_DIR}/src ) 
include_directories( ${Descent_SOURCE_DIR}/.. ) 

include ( ../CMake_Externals.txt )

if (UNIX) 

add_library(FakeGL SHARED
	src/FakeGL.cpp
)

add_executable(RenderEngineBench
	src/RenderEngineBenchmark.cpp
	src/RenderEngineBench.cpp
)
endif()

# use SDL to setup all of our open GL stuff 
add_definitions( -DUSE_SDL_OPENGL )

# static link with unix as the boost libraries are hard to get
# in the correct version  
if (UNIX)
#	target_link_libraries( RenderEngineBench boost_system )
#	target_link_libraries( RenderEngineBench boost_program_options )
endif()

target_link_libraries( RenderEngineBench DescentEngine DescentLogic FakeGL )

## perf tools 
if ( COMPILE_WITH_PROFILER )
	target_link_libraries( RenderEngineBench profiler )
endif()

