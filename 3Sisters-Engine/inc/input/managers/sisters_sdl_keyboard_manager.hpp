#pragma once

#ifndef SISTERS_SDL_KEYBOARD_MANAGER_HPP
#define SISTERS_SDL_KEYBOARD_MANAGER_HPP

#include <input/sisters_sdl_keyboard.hpp>

namespace SDL{
/* A static singleton KeyboardManager that hosts 
 several functions to hold and keep a reference of 
 the keyboard state holder to allow for simplified keyboard
 inputs. All functions and resources are static and 
 no public constructor is defined.  
*/
class KeyboardManager {
    public:
        //* setter functions

        // set the event handle to be stored
        static void SetKeyboardState(KeyboardStateHolder*  handle);

        //* getter functions

        // return the event handle
        static KeyboardStateHolder* GetKeyboardState();

    private:
        // private storage of the event handle
        static KeyboardStateHolder* keyboardState;
        
        // private constructor
        KeyboardManager() {}
};
}
#endif