cmake_minimum_required(VERSION 3.15.0)
project(Heaven-Engine VERSION 0.0.3 LANGUAGES C CXX)
cmake_policy(SET CMP0072 NEW)

# Set the install prefix to the build folder's lib directory
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}")

#Add macro
include(GNUInstallDirs)

# Grab all source files
file(GLOB_RECURSE ENGINE
    ${CMAKE_SOURCE_DIR}/src/engine/*.c
    ${CMAKE_SOURCE_DIR}/src/engine/*.cpp)

file(GLOB_RECURSE GAMEOBJS
    ${CMAKE_SOURCE_DIR}/src/gameObjs/*.c
    ${CMAKE_SOURCE_DIR}/src/gameObjs/*.cpp)

file(GLOB_RECURSE ORTHOCAM 
    ${CMAKE_SOURCE_DIR}/src/orthoCam/*.c
    ${CMAKE_SOURCE_DIR}/src/orthoCam/*.cpp)

file(GLOB_RECURSE RESOURCESYS 
    ${CMAKE_SOURCE_DIR}/src/resourceSys/*.c
    ${CMAKE_SOURCE_DIR}/src/resourceSys/*.cpp)

file(GLOB_RECURSE WINDOW 
    ${CMAKE_SOURCE_DIR}/src/window/*.c
    ${CMAKE_SOURCE_DIR}/src/window/*.cpp)

file(GLOB_RECURSE GLAD
    ${CMAKE_SOURCE_DIR}/inc/glad/*.c)

# Include directory for your engine's headers
set(ENGINE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/inc)

# Create the library
add_library(Heaven-Engine SHARED ${ENGINE} ${GAMEOBJS} ${ORTHOCAM} ${RESOURCESYS} ${GLAD} ${WINDOW})

# Include directories for header files
target_include_directories(Heaven-Engine PUBLIC
    $<BUILD_INTERFACE:${ENGINE_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:include>)

#Find all dependecies needed to compile

#*LINUX version of finding the dependencies
if(UNIX)

#Find OpenGL package
find_package(OpenGL REQUIRED)

#Find GLM package
find_package(glm REQUIRED)

#Find BOX2D
find_package(glfw3 REQUIRED)

#Find GLFW
find_package(box2d REQUIRED)

 # Put together all necessary libs into one variable
 set(LIBS OpenGL glm box2d glfw)
    
 # Get Xorg dependencies into one variable
 set(Xorg Xxf86vm X11 Xrandr pthread Xi)

#Make copies of the libraries .so files

# Link against OpenGL and GLM
target_link_libraries(Heaven-Engine PUBLIC ${LIBS} ${Xorg})

endif(UNIX)

#*WINDOWS version of finding the dependencies
#TODO: Still need to finish configuring this on windows
if(WIN32)

#OpenGL
find_package(OpenGL REQUIRED)

#GLM
find_package(GLM REQUIRED)

#GLFW
find_package(GLFW3 REQUIRED)

#box2d
find_package(BOX2D REQUIRED)

set(LIBS glfw3 opengl32 box2d)

# Link against OpenGL and GLM
target_link_libraries(Heaven-Engine PRIVATE ${LIBS})

#Copy all the dlls into the build folder
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
		"${PROJECT_SOURCE_DIR}/dlls"
		$<TARGET_FILE_DIR:${PROJECT_NAME}>)

endif(WIN32)

# Install the library and CMake configuration files
install(TARGETS ${PROJECT_NAME} EXPORT Heaven-EngineConfig
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
	)

install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/inc
    DESTINATION "${CMAKE_BINARY_DIR}"
)
    
# Configure the package and specify the export destination
install(EXPORT Heaven-EngineConfig
    DESTINATION ${CMAKE_BINARY_DIR}
)
export(TARGETS ${PROJECT_NAME} FILE Heaven-Engine.cmake)