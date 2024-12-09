#include <input/sdl_keyboard_manager.hpp>

using namespace SDL;

//? debug outputs
#include <iostream>
#include <SDL2/SDL.h>

KeyboardStateHolder*  KeyboardManager::keyboardState = nullptr;

void KeyboardManager::SetKeyboardState(KeyboardStateHolder*  handle){
    // check if SDL has been initialized
    if(SDL_WasInit(SDL_INIT_EVERYTHING) == 0){
        std::cout << "ERROR: SDL hasn't been initialized!\n";
        return; // stop function
    }

    // set the window
    if(handle != nullptr)
        // set to track handle
        keyboardState = handle;
    else{
        std::cout << "ERROR: given keyboard state is empty!\n";
        return; // stop function
    }
}

KeyboardStateHolder* KeyboardManager::GetKeyboardState(){
    // check if handle is not set
    if(keyboardState == nullptr){
        std::cout << "ERROR: event handle hasn't been set, returning an empty handle\n";
        return nullptr; // return nothing
    }

    return keyboardState;
}