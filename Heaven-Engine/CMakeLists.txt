cmake_minimum_required(VERSION 3.15.0)
set (CMAKE_CXX_STANDARD 17)
project(Heaven-Engine VERSION 0.1.0 LANGUAGES C CXX)
project(Heaven-Engine-s VERSION 0.1.0 LANGUAGES C CXX)
cmake_policy(SET CMP0072 NEW)

# Set the install prefix to the build folder's lib directory
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}")

# Grab all source files
file(GLOB_RECURSE ENGINE
    ${CMAKE_SOURCE_DIR}/src/engine/*.c
    ${CMAKE_SOURCE_DIR}/src/engine/*.cpp)

file(GLOB_RECURSE GAMEOBJS
    ${CMAKE_SOURCE_DIR}/src/gameObjects/*.c
    ${CMAKE_SOURCE_DIR}/src/gameObjects/*.cpp)

file(GLOB_RECURSE CAMERAS 
    ${CMAKE_SOURCE_DIR}/src/cameras/*.c
    ${CMAKE_SOURCE_DIR}/src/cameras/*.cpp)

file(GLOB_RECURSE RESOURCESYS 
    ${CMAKE_SOURCE_DIR}/src/resourceSystems/*.c
    ${CMAKE_SOURCE_DIR}/src/resourceSystems/*.cpp)

file(GLOB_RECURSE WINDOW 
    ${CMAKE_SOURCE_DIR}/src/window/*.c
    ${CMAKE_SOURCE_DIR}/src/window/*.cpp)

file(GLOB_RECURSE GLAD
    ${CMAKE_SOURCE_DIR}/src/glad/*.c
    ${CMAKE_SOURCE_DIR}/src/glad/*.cpp)

file(GLOB_RECURSE SOUNDCOMPONENTS
    ${CMAKE_SOURCE_DIR}/src/soundComponents/*.c
    ${CMAKE_SOURCE_DIR}/src/soundComponents/*.cpp)

file(GLOB_RECURSE UTILITY
    ${CMAKE_SOURCE_DIR}/src/utilities/*.c
    ${CMAKE_SOURCE_DIR}/src/utilities/*.cpp
)

# Include directory for your engine's headers
set(ENGINE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/inc)

# Create both shared and static libraries
add_library(Heaven-Engine SHARED ${ENGINE} ${GAMEOBJS} ${CAMERAS} ${RESOURCESYS} ${UTILITY} ${GLAD} ${WINDOW} ${SOUNDCOMPONENTS})
add_library(Heaven-Engine-s STATIC ${ENGINE} ${GAMEOBJS} ${CAMERAS} ${RESOURCESYS} ${UTILITY} ${GLAD} ${WINDOW} ${SOUNDCOMPONENTS})

# Include directories for header files
target_include_directories(Heaven-Engine PUBLIC
    $<BUILD_INTERFACE:${ENGINE_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:include>)

target_include_directories(Heaven-Engine-s PUBLIC
    $<BUILD_INTERFACE:${ENGINE_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:include>)

# Find all dependencies needed to compile

# *LINUX version of finding the dependencies
if(UNIX)
    # Find OpenGL package
    find_package(OpenGL REQUIRED)

    # Find GLM package
    find_package(glm CONFIG REQUIRED)

    # Find BOX2D
    find_package(glfw3 CONFIG REQUIRED)

    # Find GLFW
    find_package(box2d CONFIG REQUIRED)

    # Find OpenAL
    find_package(OpenAL CONFIG REQUIRED)

    # Find SNDFile
    find_package(SndFile CONFIG REQUIRED)

    # Find FreeType2
    find_package(Freetype REQUIRED)

    # Put together all necessary libs into one variable
    set(LIBS OpenGL glm box2d glfw Freetype::Freetype sndfile)

    # Get Xorg dependencies into one variable
    set(Xorg Xxf86vm X11 Xrandr pthread Xi openal udev ogg vorbis vorbisenc vorbisfile)

    # Grab GLFW dirs
    target_link_directories(Heaven-Engine PUBLIC ${GLFW3_INCLUDE_DIR})
    target_link_directories(Heaven-Engine-s PUBLIC ${GLFW3_INCLUDE_DIR})

    # Link against all libraries used
    target_link_libraries(Heaven-Engine PUBLIC ${LIBS} ${Xorg})
    target_link_libraries(Heaven-Engine-s PUBLIC ${LIBS} ${Xorg})
endif(UNIX)

# *WINDOWS version of finding the dependencies
if(WIN32)
    # OpenGL
    find_package(OpenGL REQUIRED)

    # GLM
    find_package(glm CONFIG REQUIRED)

    # GLFW
    find_package(GLFW3 REQUIRED)

    # BOX2D
    find_package(BOX2D CONFIG REQUIRED)

    # Find OpenAL
    find_package(OpenAL CONFIG REQUIRED)

    # Find SNDFile
    find_package(SndFile CONFIG REQUIRED)

    # Find Freetype
    find_package(Freetype REQUIRED)

    if(MSVC)
        # Put together all necessary libs into one variable
        set(LIBS opengl32 glm::glm box2d::box2d glfw OpenAL::OpenAL Freetype::Freetype SndFile::sndfile)

        # Grab GLFW headers
        target_link_directories(Heaven-Engine PUBLIC ${GLFW_INCLUDE_DIR})
        target_link_directories(Heaven-Engine-s PUBLIC ${GLFW_INCLUDE_DIR})

        # Grab GLM headers
        target_link_directories(Heaven-Engine PUBLIC ${GLM_INCLUDE_DIR})
        target_link_directories(Heaven-Engine-s PUBLIC ${GLM_INCLUDE_DIR})

    else(MSVC)
        # Put together all necessary libs into one variable
        set(LIBS opengl32 glm box2d glfw openal Freetype::Freetype sndfile)

        # Grab GLFW headers
        target_link_directories(Heaven-Engine PUBLIC ${GLFW3_INCLUDE_DIR})
        target_link_directories(Heaven-Engine-s PUBLIC ${GLFW3_INCLUDE_DIR})

        # Grab GLM headers
        target_link_directories(Heaven-Engine PUBLIC ${GLM_INCLUDE_DIR})
        target_link_directories(Heaven-Engine-s PUBLIC ${GLM_INCLUDE_DIR})
    endif(MSVC)

    # Link against OpenGL and GLM
    target_link_libraries(Heaven-Engine PRIVATE ${LIBS})
    target_link_libraries(Heaven-Engine-s PRIVATE ${LIBS})
endif(WIN32)

# Install the library and CMake configuration files
install(TARGETS Heaven-Engine EXPORT Heaven-EngineConfig
    ARCHIVE DESTINATION ${CMAKE_BINARY_DIR}
    LIBRARY DESTINATION ${CMAKE_BINARY_DIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Install the library and CMake configuration files
install(TARGETS Heaven-Engine-s EXPORT Heaven-Engine-sConfig
    ARCHIVE DESTINATION ${CMAKE_BINARY_DIR}
    LIBRARY DESTINATION ${CMAKE_BINARY_DIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/inc/
    DESTINATION "${CMAKE_SOURCE_DIR}/build/include"
)

# Configure the package and specify the export destination
install(EXPORT Heaven-EngineConfig
    DESTINATION ${CMAKE_BINARY_DIR}
)

# Configure the package and specify the export destination
install(EXPORT Heaven-Engine-sConfig
    DESTINATION ${CMAKE_BINARY_DIR}
)

export(TARGETS Heaven-Engine FILE Heaven-Engine.cmake)

export(TARGETS Heaven-Engine-s FILE Heaven-Engine-s.cmake)