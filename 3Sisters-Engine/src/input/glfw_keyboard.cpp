#include <input/glfw_keyboard.hpp>

// include Keyboard Manager
#include <input/glfw_keyboard_manager.hpp>

using namespace GLFW;

bool GLFW::getKeyInput(int key){
    // check for input using GLFW
    if(glfwGetKey(&KeyboardManager::GetWindowHandle(), key) == GLFW_PRESS){
        // return true if the key was pressed
        return true;
    }

    // return false if the key wasn't pressed
    return false;
}

bool GLFW::getKeyInputDown(int key){
    // check for input using GLFW
    if(glfwGetKey(&KeyboardManager::GetWindowHandle(), key) == GLFW_PRESS){
        // return true if the key was pressed
        return true;
    }

    // return false if the key wasn't pressed
    return false;
}

bool GLFW::getKeyInputUp(int key){
    // check for input using GLFW
    if(glfwGetKey(&KeyboardManager::GetWindowHandle(), key) == GLFW_RELEASE){
        // return true if the key was pressed
        return true;
    }

    // return false if the key wasn't pressed
    return false;
}