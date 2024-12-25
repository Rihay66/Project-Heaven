#pragma once

#ifndef SDL_GAMEPAD_HPP
#define SDL_GAMEPAD_HPP

// include memory lib
#include <memory>

// include SDL
#include <SDL2/SDL_gamecontroller.h>

namespace SDL{

//? Gamepad macros
constexpr int NULL_GAMEPAD = -1;

// define structure of a game controller device
struct ControllerDevice{
    // default is a non existant device
    int ID = NULL_GAMEPAD;
    // connection boolean
    bool isConnected = false;
    // keep reference of the controller
    SDL_GameController* controller = nullptr;
};

// define structure of a gamepad
struct Gamepad{
    // contain a shared reference of a controller device
    std::shared_ptr<ControllerDevice> device;
};

//? Gamepad functions

/* button callback of the gamepad which checks for the given button
* @NOTE: Requires a set gamepad
*/ 
bool getButtonInput(Gamepad& pad, SDL_GameControllerButton key);

/* axis callback of the gamepad which returns a incremental value when there is input of the given key
* @NOTE: Requires a set gamepad
*/
float getAxisRawInput(Gamepad& pad, SDL_GameControllerAxis key, float deadzone = 0.5f);

/* axis callback of the gamepad which returns a value of direction when there is input of the given key
* @NOTE: Requires a set gamepad
*/
float getAxisInput(Gamepad& pad, SDL_GameControllerAxis key, float deadzone = 0.5f);

}

#endif