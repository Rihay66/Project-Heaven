cmake_minimum_required(VERSION 3.5.0)
project(project-heaven VERSION 0.0.1)
cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)

add_executable(project-heaven 
src/main.cpp
src/window.cpp
src/renderer.cpp
glad/glad.c
glad/glad.h
inc/window.h
inc/renderer.h

)

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