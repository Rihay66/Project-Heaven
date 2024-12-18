#pragma once

#ifndef SDL_KEYBOARD_HPP
#define SDL_KEYBOARD_HPP

#include <sys/types.h>

// define a keyboard state holder
struct KeyboardStateHolder{
    u_int8_t* keyboardState;
};

namespace SDL{
/* Host several functions to allow for keyboard inputs
*/

/* key callback of the keyboard which checks for the given scancode
* NOTE: Checks if key was pressed
*/
bool getKeyInput(int scancode);

/* key callback of the keyboard which checks for the given scancode
* NOTE: Checks if key was pressed, similar to getKeyInput
*/
bool getKeyInputDown(int scancode);

//TODO: Figure out how to implement getKeyInputUp, when a key gets pressed and then released

}
#endif