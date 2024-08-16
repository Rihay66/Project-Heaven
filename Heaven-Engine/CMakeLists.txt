cmake_minimum_required(VERSION 3.15.0)
set (CMAKE_CXX_STANDARD 20)
project(Heaven-Engine VERSION 0.1.3 LANGUAGES C CXX)
project(Heaven-Engine-s VERSION 0.1.3 LANGUAGES C CXX)
project(Engine-Testing VERSION 0.1.0 LANGUAGES C CXX)
cmake_policy(SET CMP0072 NEW)

# Set the install prefix to the build folder's lib directory
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}")

# Check if ImGUI is set up
file(GLOB RESULT ${CMAKE_SOURCE_DIR}/imgui/*)
list(LENGTH RESULT RES_LEN)
if(RES_LEN EQUAL 0)
# ImGUI directory empty throw an error
message(SEND_ERROR "ERROR: ImGUI directory is Empty, verify that all git submodule were initialized and updated")
endif()

# Grab all ImGUI source files
file(GLOB IMGUI
    ${CMAKE_SOURCE_DIR}/imgui/*.cpp
    ${CMAKE_SOURCE_DIR}/imgui/backends/imgui_impl_opengl3.cpp
    ${CMAKE_SOURCE_DIR}/imgui/backends/imgui_impl_glfw.cpp
)

# Grab all source files
file(GLOB_RECURSE ENGINE
    ${CMAKE_SOURCE_DIR}/src/engine/*.c
    ${CMAKE_SOURCE_DIR}/src/engine/*.cpp)

file(GLOB_RECURSE ECS
    ${CMAKE_SOURCE_DIR}/src/ecs/*.c
    ${CMAKE_SOURCE_DIR}/src/ecs/*.cpp
    ${CMAKE_SOURCE_DIR}/src/ecs/managers/*.c
    ${CMAKE_SOURCE_DIR}/src/ecs/managers/*.cpp
    ${CMAKE_SOURCE_DIR}/src/systems/*.c
    ${CMAKE_SOURCE_DIR}/src/systems/*.cpp)

file(GLOB_RECURSE STB
    ${CMAKE_SOURCE_DIR}/src/stb/*.c
    ${CMAKE_SOURCE_DIR}/src/stb/*.cpp)

file(GLOB_RECURSE CAMERAS 
    ${CMAKE_SOURCE_DIR}/src/cameras/*.c
    ${CMAKE_SOURCE_DIR}/src/cameras/*.cpp)

file(GLOB_RECURSE RESOURCESYS 
    ${CMAKE_SOURCE_DIR}/src/resourceSystems/*.c
    ${CMAKE_SOURCE_DIR}/src/resourceSystems/*.cpp
    ${CMAKE_SOURCE_DIR}/src/resourceSystems/managers/*.c
    ${CMAKE_SOURCE_DIR}/src/resourceSystems/managers/*.cpp)

file(GLOB_RECURSE WINDOW 
    ${CMAKE_SOURCE_DIR}/src/window/*.c
    ${CMAKE_SOURCE_DIR}/src/window/*.cpp)

file(GLOB_RECURSE GLAD
    ${CMAKE_SOURCE_DIR}/src/glad/*.c
    ${CMAKE_SOURCE_DIR}/src/glad/*.cpp)

file(GLOB_RECURSE SOUNDENGINE
    ${CMAKE_SOURCE_DIR}/src/soundEngine/*.c
    ${CMAKE_SOURCE_DIR}/src/soundEngine/*.cpp)

file(GLOB_RECURSE UTILITY
    ${CMAKE_SOURCE_DIR}/src/utilities/*.c
    ${CMAKE_SOURCE_DIR}/src/utilities/*.cpp
)

# Include directory for your engine's headers
set(ENGINE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/inc)

# Create both shared and static libraries
add_library(Heaven-Engine SHARED ${ENGINE} ${ECS} ${STB} ${CAMERAS} ${RESOURCESYS} ${UTILITY} ${GLAD} ${WINDOW} ${SOUNDENGINE} ${IMGUI})
add_library(Heaven-Engine-s STATIC ${ENGINE} ${ECS} ${STB} ${CAMERAS} ${RESOURCESYS} ${UTILITY} ${GLAD} ${WINDOW} ${SOUNDENGINE} ${IMGUI})

# Include directories for header files
target_include_directories(Heaven-Engine PUBLIC
    $<BUILD_INTERFACE:${ENGINE_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:include>
)

target_include_directories(Heaven-Engine PRIVATE
    ${CMAKE_SOURCE_DIR}/imgui
    ${CMAKE_SOURCE_DIR}/imgui/backends
)

target_include_directories(Heaven-Engine-s PUBLIC
    $<BUILD_INTERFACE:${ENGINE_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:include>
)

target_include_directories(Heaven-Engine-s PRIVATE
    ${CMAKE_SOURCE_DIR}/imgui
    ${CMAKE_SOURCE_DIR}/imgui/backends
)

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
endif ()

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
    endif()

    # Link against OpenGL and GLM
    target_link_libraries(Heaven-Engine PRIVATE ${LIBS})
    target_link_libraries(Heaven-Engine-s PRIVATE ${LIBS})
endif()

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

# Optionally, conditionally install the executable
option(BUILD_ENGINE_TESTING "Build Engine-Testing executable" OFF)

# Test program

if(BUILD_ENGINE_TESTING)

# Include all files
file(GLOB_RECURSE SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/test/src/*.c
    ${CMAKE_SOURCE_DIR}/test/src/*.cpp
    ${CMAKE_SOURCE_DIR}/test/*.cpp
)

file(GLOB_RECURSE HEADER_FILES
    ${CMAKE_SOURCE_DIR}/test/inc/*.h
    ${CMAKE_SOURCE_DIR}/test/inc/*.hpp
)

# Define resource folders
set(SHADERS_DIR ${CMAKE_SOURCE_DIR}/shaders)
set(FONTS_DIR ${CMAKE_SOURCE_DIR}/fonts)
set(TEXTURES_DIR "${CMAKE_SOURCE_DIR}/test/textures")
set(SOUNDS_DIR "${CMAKE_SOURCE_DIR}/test/sounds")

# Define the destination build folder
set(BUILD_DIR ${CMAKE_BINARY_DIR})

# Create folders and their sub files for runtime loading
# Function to copy files if they are different
function(copy_if_different SRC_DIR DEST_DIR)
    # Remove the existing destination directory
    if(EXISTS ${DEST_DIR})
        file(REMOVE_RECURSE ${DEST_DIR})
    endif()

    # Create the destination directory if it doesn't exist
    file(MAKE_DIRECTORY ${DEST_DIR})

    # Copy over the files
    file(GLOB_RECURSE FILES_LIST "${SRC_DIR}/*")
    foreach(FILE_PATH ${FILES_LIST})
        get_filename_component(FILE_NAME ${FILE_PATH} NAME)
        set(DEST_FILE_PATH "${DEST_DIR}/${FILE_NAME}")
        configure_file(${FILE_PATH} ${DEST_FILE_PATH} COPYONLY)
    endforeach()
endfunction()

# Check if detected OS is LINUX
if(UNIX)

# Create executable
add_executable(Engine-Testing
${HEADER_FILES}
${SOURCE_FILES}
)

# Call the function for each resource folder
copy_if_different(${SHADERS_DIR} ${BUILD_DIR}/shaders)
copy_if_different(${TEXTURES_DIR} ${BUILD_DIR}/textures)
copy_if_different(${SOUNDS_DIR} ${BUILD_DIR}/sounds)
copy_if_different(${FONTS_DIR} ${BUILD_DIR}/fonts)

# Link the extra packages their include directories to avoid linking errors
target_include_directories(Engine-Testing PRIVATE Heaven-Engine)
# Link the Heaven-Engine to executable
target_link_libraries(Engine-Testing PRIVATE Heaven-Engine)

endif ()

if(WIN32)

# Create executable
add_executable(Engine-Testing
${HEADER_FILES}
${SOURCE_FILES}
)

# Call the function for each resource folder
copy_if_different(${SHADERS_DIR} ${BUILD_DIR}/shaders)
copy_if_different(${TEXTURES_DIR} ${BUILD_DIR}/textures)
copy_if_different(${SOUNDS_DIR} ${BUILD_DIR}/sounds)
copy_if_different(${FONTS_DIR} ${BUILD_DIR}/fonts)

if(MSVC) # msvc

#GLM
find_package(GLM CONFIG REQUIRED)

#GLFW
find_package(GLFW3 CONFIG REQUIRED)

#box2d
find_package(BOX2D CONFIG REQUIRED)

# Find OpenAL
find_package(OpenAL CONFIG REQUIRED)

# Find SNDFile
find_package(SndFile CONFIG REQUIRED)

#Find Freetype
find_package(Freetype REQUIRED)

# Link the extra packages their include directories to avoid linking errors
target_include_directories(Engine-Testing PRIVATE Heaven-Engine-s glm::glm glfw box2d::box2d OpenAL::OpenAL Freetype::Freetype SndFile::sndfile)
# Link the Heaven-Engine to executable
target_link_libraries(Engine-Testing PRIVATE Heaven-Engine-s glm::glm glfw box2d::box2d OpenAL::OpenAL Freetype::Freetype SndFile::sndfile)

else () # mingw

# Link the extra packages their include directories to avoid linking errors
target_include_directories(Engine-Testing PRIVATE Heaven-Engine)
# Link the Heaven-Engine to executable
target_link_libraries(Engine-Testing PRIVATE Heaven-Engine)
endif()

endif ()

endif()