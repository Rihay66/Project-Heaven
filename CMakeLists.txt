cmake_minimum_required(VERSION 3.5.0)
project(project-heaven VERSION 0.0.1 LANGUAGES C CXX)
cmake_policy(SET CMP0072 NEW)

#include all files
# TODO auto get source files and header files from /inc and /src
add_executable(project-heaven 
src/main.cpp
src/window.cpp
src/renderer.cpp
src/texture.cpp
src/shader.cpp
src/stb_image.cpp
src/resourceManager.cpp
src/gameHandler.cpp
src/camera.cpp
src/gameObject.cpp
src/player.cpp
src/physics.cpp
src/rigidbodyObject.cpp
glad/glad.c
glad/glad.h
inc/camera.hpp
inc/physics.hpp
inc/player.hpp
inc/gameObject.hpp
inc/window.hpp
inc/gameHandler.hpp
inc/rigidbodyObject.hpp
inc/renderer.hpp
inc/texture.hpp
inc/stb_image.h
inc/shader.hpp
inc/resourceManager.hpp
)
# Create folders and thier sub files for runtime loading
file(CREATE_LINK "${PROJECT_SOURCE_DIR}/textures" "${CMAKE_CURRENT_BINARY_DIR}/textures" SYMBOLIC)

file(CREATE_LINK "${PROJECT_SOURCE_DIR}/shaders" "${CMAKE_CURRENT_BINARY_DIR}/shaders" SYMBOLIC)

# We need a CMAKE_DIR with some code to find external dependencies
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

#OpenGL
find_package(OpenGL REQUIRED)

#GLM
find_package(GLM REQUIRED)
message(STATUS "GLM included at ${GLM_INCLUDE_DIR}")

#GLFW
find_package(GLFW3 REQUIRED)
message(STATUS "Found GLFW3 in ${GLFW3_INCLUDE_DIR}")

#box2d
find_package(BOX2D REQUIRED)
message(STATUS "Found BOX2D in ${BOX2D_INCLUDE_DIR}")

# Link libs if the detected OS is LINUX
if(UNIX)

target_link_libraries(project-heaven 
glfw 
OpenGL::GL
Xxf86vm
OpenGL::GLU
X11
Xrandr
pthread
Xi
box2d
)
endif (UNIX)

# Link libs if the detected OS is Windows
# NOTE was compiled using msys2's w64-x86_64 packages
if(WIN32)

set(LIBS glfw3 opengl32 box2d)

# Define the include DIRs
include_directories(
	"${CMAKE_SOURCE_DIR}/src"
	"${CMAKE_SOURCE_DIR}/include"
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		"${PROJECT_SOURCE_DIR}/dlls"
		$<TARGET_FILE_DIR:${PROJECT_NAME}>)

target_link_libraries(project-heaven 
${LIBS}
)

endif(WIN32)