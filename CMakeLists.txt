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
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}Heaven-Engine/build/CMakeFiles/Export/a58a60f24887ba09385dfba63e9906cb)

find_package(Heaven-Engine REQUIRED)

find_package(glfw3 REQUIRED)

target_link_libraries(project-heaven PRIVATE Heaven-Engine glfw)

endif (UNIX)

# Link libs if the detected OS is Windows
# NOTE was compiled using msys2's w64-x86_64 packages
if(WIN32)


endif(WIN32)