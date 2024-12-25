#include <input/sdl_keyboard.hpp>

// include keyboard manager
#include <input/sdl_keyboard_manager.hpp>

using namespace SDL;

bool SDL::getKeyInput(int key){
    // grab the keyboard state holder, then check for given scancode when pressed down
    if(KeyboardManager::GetKeyboardState()->keyboardState[key] > 0){
        return true;
    }

    return false;
}

bool SDL::getKeyInputDown(int key){
    // grab the keyboard state holder, then check for given scancode when pressed down
    if(KeyboardManager::GetKeyboardState()->keyboardState[key] > 0){
        return true;
    }

    return false;
}

bool SDL::getKeyInputUp(int key){
    // grab the keyboard state holder, then check for given scancode when not pressed
    if(KeyboardManager::GetKeyboardState()->keyboardState[key] == 0){
        return true;
    }

    return false;
}