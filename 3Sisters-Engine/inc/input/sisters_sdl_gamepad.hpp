#pragma once

#ifndef SISTERS_SDL_GAMEPAD_HPP
#define SISTERS_SDL_GAMEPAD_HPP

// include SDL
#include <SDL3/SDL.h>

namespace SDL{

// define structure of a gamepad
struct Gamepad{
    // connection state of this gamepad
    bool isConnected = false;
    // keep reference of the controller
    SDL_Gamepad* device = nullptr;
};

//? Gamepad functions

/* button callback of the gamepad which checks for the given button
* @NOTE: Requires a set gamepad
*/ 
bool getButtonInput(Gamepad& pad, SDL_GamepadButton key);

/* axis callback of the gamepad which returns a incremental value when there is input of the given key
* @NOTE: Requires a set gamepad
*/
float getAxisRawInput(Gamepad& pad, SDL_GamepadAxis key, float deadzone = 0.5f);

/* axis callback of the gamepad which returns a value of direction when there is input of the given key
* @NOTE: Requires a set gamepad
*/
float getAxisInput(Gamepad& pad, SDL_GamepadAxis key, float deadzone = 0.5f);

}

#endif