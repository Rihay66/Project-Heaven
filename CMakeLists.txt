cmake_minimum_required(VERSION 3.15.0)
project(project-heaven VERSION 0.0.1 LANGUAGES C CXX)
cmake_policy(SET CMP0072 NEW)

#include all files
# Add source files
file(GLOB_RECURSE SOURCE_FILES 
	${CMAKE_SOURCE_DIR}/src/*.c
	${CMAKE_SOURCE_DIR}/src/*.cpp)

# Add header files
file(GLOB_RECURSE HEADER_FILES 
	${CMAKE_SOURCE_DIR}/inc/*.h
	${CMAKE_SOURCE_DIR}/inc/*.hpp)

#include all files
add_executable(project-heaven 
${HEADER_FILES} 
${SOURCE_FILES}
)

# Create folders and thier sub files for runtime loading
file(CREATE_LINK "${PROJECT_SOURCE_DIR}/textures" "${CMAKE_CURRENT_BINARY_DIR}/textures" SYMBOLIC)

file(CREATE_LINK "${PROJECT_SOURCE_DIR}/shaders" "${CMAKE_CURRENT_BINARY_DIR}/shaders" SYMBOLIC)

# Link libs if the detected OS is LINUX
if(UNIX)

# Add the path to your engine library's CMake configuration files
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}Heaven-Engine/build)

add_library(Heaven-Engine SHARED IMPORTED)
set_target_properties(Heaven-Engine PROPERTIES
    IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/Heaven-Engine/build/lib/libHeaven-Engine.so
    INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/Heaven-Engine/build/include
)

find_package(glfw3 REQUIRED)

target_link_libraries(project-heaven PRIVATE Heaven-Engine glfw)

endif (UNIX)

# Link libs if the detected OS is Windows
# NOTE was compiled using msys2's w64-x86_64 packages
if(WIN32)

# Specify the path to Heaven-EngineConfig.cmake
set(Heaven-Engine_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Heaven-Engine/build")

#Get the engine library
find_package(Heaven-Engine REQUIRED)

find_package(glfw3 REQUIRED)

target_link_libraries(project-heaven PRIVATE Heaven-Engine glfw)

# Define the source and destination paths for the DLL of the Heaven Engine
set(ENGINE_DLL_SOURCE "${CMAKE_SOURCE_DIR}/Heaven-Engine/build/libHeaven-Engine.dll")
set(ENGINE_DLL_DEST "${CMAKE_BINARY_DIR}")

# Use file(COPY ...) to copy the DLL
file(COPY "${ENGINE_DLL_SOURCE}" DESTINATION "${ENGINE_DLL_DEST}")

# Make sure your external project knows where to find the copied DLL
add_definitions(-DHEAVEN_ENGINE_DLL_PATH="${ENGINE_DLL_DEST}")

endif(WIN32)