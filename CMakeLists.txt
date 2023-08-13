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
src/rigidbodyObject.cpp
glad/glad.c
glad/glad.h
inc/camera.hpp
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

# Link libs if the detected OS is LINUX
if(UNIX)

find_package(OpenGL REQUIRED)

target_link_libraries(project-heaven 
glfw 
OpenGL::GL
Xxf86vm
OpenGL::GLU
X11
Xrandr
pthread
Xi
)
endif (UNIX)

# Link libs if the detected OS is Windows
# NOTE was compiled using msys2's w64-x86_64 packages
if(WIN32)

find_package(OpenGL REQUIRED)

target_link_libraries(project-heaven 
glfw3
OpenGL::GL
OpenGL::GLU
)

endif(WIN32)