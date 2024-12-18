#include <input/glfw_gamepad.hpp>

bool GLFW::getButtonInput(GLFW::Gamepad &pad, int key){
    // check if gamepad is set and connected
    if(pad.device != nullptr && pad.device->isConnected){
        // check state of given key
        if(pad.device->state.buttons[key] == GLFW_PRESS){
            return true;
        }
    }

    return false;
}

float GLFW::getAxisRawInput(GLFW::Gamepad &pad, int key, float deadzone){
    // check that the pad is set and the state is valid
    if(pad.device != nullptr && pad.device->isConnected){
        //check for positive and negative values above deadzone
        if(pad.device->state.axes[key] < -deadzone){
            return pad.device->state.axes[key];
        }else if(pad.device->state.axes[key] > deadzone){
            return pad.device->state.axes[key];
        }
    }

    // return 0 for no input
    return 0.0f;
}

float GLFW::getAxisInput(GLFW::Gamepad& pad, int key, float deadzone){
    // check the that pad is set and the state is valid
    if(pad.device != nullptr && pad.device->isConnected){
        //check for positive and negative values above deadzone
        if(pad.device->state.axes[key] < -deadzone){
            return -1.0f;
        }else if(pad.device->state.axes[key] > deadzone){
            return 1.0f;
        }
    }

    // return 0 for no input
    return 0.0f;
}