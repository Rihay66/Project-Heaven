#pragma once

#ifndef SISTERS_SDL_KEYBOARD_HPP
#define SISTERS_SDL_KEYBOARD_HPP

#include <stdint.h>

// define a keyboard state holder
struct KeyboardStateHolder{
    uint8_t* keyboardState;
};

namespace SDL{
/* Host several functions to allow for keyboard inputs
*/

/* key callback of the keyboard which checks for the given scancode
* @NOTE: Checks if key was pressed
*/
bool getKeyInput(int scancode);

/* key callback of the keyboard which checks for the given scancode
* @NOTE: Checks if key was pressed, similar to getKeyInput
*/
bool getKeyInputDown(int scancode);

/* key callback of the keyboard which checks for the given scancode
* @NOTE: Check if key was released
*/
bool getKeyInputUp(int scancode);

}
#endif