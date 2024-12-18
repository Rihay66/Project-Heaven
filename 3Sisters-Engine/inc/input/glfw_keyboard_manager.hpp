#pragma once

#ifndef GLFW_KEYBOARD_MANAGER_HPP
#define GLFW_KEYBOARD_MANAGER_HPP

#include <GLFW/glfw3.h>

#include <input/glfw_keyboard.hpp>

namespace GLFW{
/* A static singleton KeyboardManager that hosts 
 several functions to hold and keep a reference of 
 the window handle to allow for simplified keyboard
 inputs. All functions and resources are static and 
 no public constructor is defined.  
*/
class KeyboardManager {
    public:
        //* setter functions

        // set the window handle to be stored
        static void SetWindowHandle(GLFWwindow* handle);

        //* getter functions

        // get the window handle to be used
        static GLFWwindow& GetWindowHandle();

    private:
        // private storage of the window handle
        static GLFWwindow* window;

        // private constructor
        KeyboardManager() {}
};
}
#endif