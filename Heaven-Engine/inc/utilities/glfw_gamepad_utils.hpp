#pragma once

#ifndef GLFW_GAMEPAD_UTILS_HPP
#define GLFW_GAMEPAD_UTILS_HPP
 
// include GLFW
#include <GLFW/glfw3.h>

// define basic structure of a device
struct Device{
    const char *name = "";
    // default is a non existant device
    int ID = -1;
    // connection flag, used to allow input
    bool isConnected = false;
};

// define structure of a gamepad
struct Gamepad{
    Device dev;
    // define gamepad state holder, used to further verify gamepads
    GLFWgamepadstate state;
};

//TODO: define Heaven-Engine buttons for Xbox, Playstation, and even switch

//? Playstation specific button macros
#define PLAYSTATION_BUTTON_CROSS 0
#define PLAYSTATION_BUTTON_CIRCLE 1
#define PLAYSTATION_BUTTON_SQUARE 2
#define PLAYSTATION_BUTTON_TRIANGLE 3
#define PLAYSTATION_BUTTON_L1 4
#define PLAYSTATION_BUTTON_R1 5
#define PLAYSTATION_JOYSTICK_LEFT_X 0
#define PLAYSTATION_JOYSTICK_LEFT_Y 1

//TODO: implement controller reference
// have a call back that reference GLFW input 


#endif