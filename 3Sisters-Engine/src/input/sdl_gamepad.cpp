#include <input/sdl_gamepad.hpp>

#include <cstdint>

using namespace SDL;

bool SDL::getButtonInput(Gamepad &pad, SDL_GamepadButton key){
    // check if gamepad is set and connected
    if(pad.device != nullptr && pad.device->isConnected){
        // check state of given key
        if(SDL_GetGamepadButton(pad.device->controller, key) > 0){
            return true;
        }
    }

    return false;
}

float SDL::getAxisRawInput(Gamepad &pad, SDL_GamepadAxis axis, float deadzone){
    // check if gamepad is set and connected
    if(pad.device != nullptr && pad.device->isConnected){
        // grab current value
        float input = (float)SDL_GetGamepadAxis(pad.device->controller, axis) / (float)INT16_MAX;
        // check state of given key
        if(input > deadzone){
            return input;
        }else if(input < -deadzone){
            return input;
        }
    }

    return 0.0f;
}

float SDL::getAxisInput(Gamepad &pad, SDL_GamepadAxis axis, float deadzone){
    // check if gamepad is set and connected
    if(pad.device != nullptr && pad.device->isConnected){
        // grab current value
        float input = (float)SDL_GetGamepadAxis(pad.device->controller, axis) / (float)INT16_MAX;
        // check state of given key
        if(input > deadzone){
            return 1.0f;
        }else if(input < -deadzone){
            return -1.0f;
        }
    }

    return 0.0f;
}