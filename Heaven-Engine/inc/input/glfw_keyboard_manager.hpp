#pragma once

#ifndef GLFW_KEYBOARD_MANAGER_HPP
#define GLFW_KEYBOARD_MANAGER_HPP

#include <GLFW/glfw3.h>

/* A static singleton KeyboardManager that hosts 
several functions to hold and keep a reference of 
the window handle to allow for simplified keyboard
inputs.
*/
class KeyboardManager {
    public:
        // set the window handle to be stored
        static void SetWindowHandle(GLFWwindow* handle);

        // get the window handle to be used
        static GLFWwindow& GetWindowHandle();

    private:
        // private storage of the window handle
        static GLFWwindow* window;

        // private constructor
        KeyboardManager() {}

        // auto cleaner
};

#endif