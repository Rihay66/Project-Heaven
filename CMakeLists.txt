cmake_minimum_required(VERSION 3.5.0)
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
# TODO auto get source files and header files from /inc and /src
add_executable(project-heaven 
glad/glad.c
glad/glad.h
${HEADER_FILES} 
${SOURCE_FILES}
)

# Create folders and thier sub files for runtime loading
file(CREATE_LINK "${PROJECT_SOURCE_DIR}/textures" "${CMAKE_CURRENT_BINARY_DIR}/textures" SYMBOLIC)

file(CREATE_LINK "${PROJECT_SOURCE_DIR}/shaders" "${CMAKE_CURRENT_BINARY_DIR}/shaders" SYMBOLIC)

# We need a CMAKE_DIR with some code to find external dependencies
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

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
box2d
)
endif (UNIX)

# Link libs if the detected OS is Windows
# NOTE was compiled using msys2's w64-x86_64 packages
if(WIN32)

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

set(LIBS glfw3 opengl32 box2d)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		"${PROJECT_SOURCE_DIR}/dlls"
		$<TARGET_FILE_DIR:${PROJECT_NAME}>)

target_link_libraries(project-heaven 
${LIBS}
)

endif(WIN32)