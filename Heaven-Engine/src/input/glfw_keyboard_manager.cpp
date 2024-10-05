#include <input/glfw_keyboard_manager.hpp>

//? debug outputs
#include <iostream>

// define static variables
GLFWwindow* KeyboardManager::window = nullptr;

void KeyboardManager::SetWindowHandle(GLFWwindow* handle){
    // check that GLFW has not been initialized or handle is Null
    if(glfwGetError(NULL) == GLFW_NOT_INITIALIZED || handle == nullptr){
        return; // stop function
    }

    // check if the static reference to the window is not set
    if(window == nullptr){
        // set the window
        window = handle;
    }else{
        std::cout << "ERROR: Window Handle already set!\n";
    }
}

GLFWwindow& KeyboardManager::GetWindowHandle(){
    if(window == nullptr){
        std::cout << "ERROR: Window handle hasn't been set, returning an empty handle\n";
    }

    return *window;
}

