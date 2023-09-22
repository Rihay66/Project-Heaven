cmake_minimum_required(VERSION 3.5.0)
project(Heaven-Engine VERSION 0.0.3 LANGUAGES C CXX)
cmake_policy(SET CMP0072 NEW)
#Set building type
set(CMAKE_BUILD_TYPE Release)

#include all files from engine
include_directories(../Heaven-Engine/inc)
include_directories(../Heaven-Engine/src)

file(GLOB_RECURSE ENGINE /inc/engine/*.h /inc/engine/*.hpp 
/src/engine/*.cpp /src/engine/*.c)

file(GLOB_RECURSE GAMEOBJ /inc/gameObjs/*.h /inc/gameObjs/*.hpp
/src/gameObjs/*.cpp /src/gameObjs/*.c)
file(GLOB_RECURSE GLAD inc/glad/*.h /inc/gald/*.c)
file(GLOB_RECURSE ORTHOCAM /inc/orthoCam/*.hpp
/src/orthoCam/*.cpp)
file(GLOB_RECURSE RESOURCE /inc/resourceSys/*.hpp /inc/resourceSys/*.h
/src/resourceSys/*.cpp)
file(GLOB_RECURSE WINDOW /inc/window/*.hpp
/src/window/*.cpp)

target_include_directories(Heaven-Engine PUBLIC inc src)

#generate engine as a shared library
add_library(Heaven-Engine SHARED ${ENGINE} ${GAMEOBJ} ${GLAD} ${RESOURCE} ${WINDOW})

# Install the library
install(TARGETS Heaven-Engine EXPORT engine-targets LIBRARY DESTINATION lib)

#install the header files
install(DIRECTORY inc DESTINATION inc)