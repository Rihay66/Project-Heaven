cmake_minimum_required(VERSION 3.15.0)
project(project-heaven VERSION 0.0.8 LANGUAGES C CXX)
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

# Link libs if the detected OS is LINUX
if(UNIX)

#Create folders and their sub files for runtime loading
file(COPY "${PROJECT_SOURCE_DIR}/textures" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
file(COPY "${PROJECT_SOURCE_DIR}/shaders" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
file(COPY "${PROJECT_SOURCE_DIR}/sounds" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
file(COPY "${PROJECT_SOURCE_DIR}/fonts" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

# Add the path to your engine library's CMake configuration files
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}Heaven-Engine/build)

#Make reference to the Heaven-Engine's library and it's include folder
add_library(Heaven-Engine SHARED IMPORTED)
set_target_properties(Heaven-Engine PROPERTIES
    IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/Heaven-Engine/build/lib/libHeaven-Engine.so
    INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/Heaven-Engine/build/include
)
#Make a reference to the Heaven-Engine's glfw lib 
set(local-glfw ${CMAKE_CURRENT_SOURCE_DIR}/Heaven-Engine/build/lib/libglfw.so.3.3)
#Make a reference to the Heaven-Engine's sfml-audio lib
set(local-audio ${CMAKE_CURRENT_SOURCE_DIR}/Heaven-Engine/build/lib/libsfml-audio.so.2.6.1)

#Link libraries to compile with
target_link_libraries(project-heaven PRIVATE Heaven-Engine ${local-glfw} ${local-audio})

# Define the source and destination paths for the DLL of the Heaven Engine
set(ENGINE_SO_SOURCE "${CMAKE_SOURCE_DIR}/Heaven-Engine/build/libHeaven-Engine.so")
set(SO_DEST "${CMAKE_BINARY_DIR}")

# Use file(COPY ...) to copy the SO
file(COPY "${ENGINE_SO_SOURCE}" DESTINATION "${SO_DEST}")
file(COPY ${local-glfw} DESTINATION ${SO_DEST})
file(COPY ${local-audio} DESTINATION ${SO_DEST})

# Make sure your external project knows where to find the copied SOs
add_definitions(-DHEAVEN_ENGINE_SO_PATH="${SO_DEST}")

endif (UNIX)

# Link libs if the detected OS is Windows
# NOTE was compiled using msys2's w64-x86_64 packages
if(WIN32)

# Specify the path to Heaven-Engine-sConfig.cmake
set(Heaven-Engine-s_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Heaven-Engine/build")

# Specify the path to Heaven-EngineConfig.cmake
set(Heaven-Engine_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Heaven-Engine/build")

if(MSVC)

set(BUILD_SHARED_LIBS ON)

#VC CODE
#Create a directory
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/Release)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/Release/textures)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/Release/shaders)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/Release/sounds)

#Create folders and their sub files for runtime loading
file(COPY "${PROJECT_SOURCE_DIR}/textures" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/Release")
file(COPY "${PROJECT_SOURCE_DIR}/shaders" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/Release")
file(COPY "${PROJECT_SOURCE_DIR}/sounds" DESTINATION "${CMAKE_BINARY_DIR}/Release")
file(COPY "${PROJECT_SOURCE_DIR}/fonts" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/Release")

#VS 2022
#Create directory
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/textures)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/shaders)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/sounds)

#Create folders and their sub files for runtime loading
file(COPY "${PROJECT_SOURCE_DIR}/textures" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
file(COPY "${PROJECT_SOURCE_DIR}/shaders" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
file(COPY "${PROJECT_SOURCE_DIR}/sounds" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
file(COPY "${PROJECT_SOURCE_DIR}/fonts" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

#Get the engine library
find_package(Heaven-Engine-s REQUIRED)

#GLM
find_package(GLM CONFIG REQUIRED)

#GLFW
find_package(GLFW3 REQUIRED REQUIRED)

#box2d
find_package(BOX2D CONFIG REQUIRED)

#Find SFML
find_package(SFML COMPONENTS audio REQUIRED)

#Find Freetype
find_package(Freetype REQUIRED)

target_include_directories(project-heaven PUBLIC glm::glm glfw box2d::box2d Freetype::Freetype)
target_link_libraries(project-heaven PUBLIC Heaven-Engine-s glm::glm glfw box2d::box2d sfml-audio)

# Define the source and destination paths for the DLL of the Heaven Engine
set(ENGINE_DLL_SOURCE "${CMAKE_SOURCE_DIR}/Heaven-Engine/build/Release/Heaven-Engine-s.lib")
# Define the path box2d from the Heaven-Engine
set(local-box2d )

set(DLL_DEST "${CMAKE_BINARY_DIR}")

file(COPY ${local-box2d} DESTINATION ${DLL_DEST})

else(MSVC)

#Create folders and their sub files for runtime loading
file(COPY "${PROJECT_SOURCE_DIR}/textures" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
file(COPY "${PROJECT_SOURCE_DIR}/shaders" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
file(COPY "${PROJECT_SOURCE_DIR}/sounds" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
file(COPY "${PROJECT_SOURCE_DIR}/fonts" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

#Get the engine library
find_package(Heaven-Engine REQUIRED)

#Make a reference to the Heaven-Engine's sfml-audio lib
set(local-audio ${CMAKE_CURRENT_SOURCE_DIR}/Heaven-Engine/build/lib/libsfml-audio-s.a)

# Define the source and destination paths for the DLL of the Heaven Engine
set(ENGINE_DLL_SOURCE "${CMAKE_SOURCE_DIR}/Heaven-Engine/build/libHeaven-Engine.dll")

#Make a reference to the Heaven-Engine's glfw lib 
set(local-glfw ${CMAKE_CURRENT_SOURCE_DIR}/Heaven-Engine/build/lib/glfw3.dll)

target_link_libraries(project-heaven PUBLIC Heaven-Engine ${local-glfw} ${local-audio})

set(DLL_DEST "${CMAKE_BINARY_DIR}")

endif(MSVC)

# Use file(COPY ...) to copy the DLL
file(COPY "${ENGINE_DLL_SOURCE}" DESTINATION "${DLL_DEST}")
file(COPY ${local-glfw} DESTINATION ${DLL_DEST})
file(COPY ${local-audio} DESTINATION ${DLL_DEST})

# Make sure your external project knows where to find the copied DLL
add_definitions(-DHEAVEN_ENGINE_DLL_PATH="${DLL_DEST}")

endif(WIN32)