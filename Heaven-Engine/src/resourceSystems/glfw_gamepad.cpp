#include <resourceSystems/glfw_gamepad.hpp>

Controller::Controller(Gamepad* gamepad){
    // check that GLFW has been initialized
    if(glfwGetError(NULL) == GLFW_NOT_INITIALIZED){
        pad = nullptr; // the pad is undefined
    }else{
        pad = gamepad;
    }
}

Controller::~Controller(){
    // clear resources and references
    this->pad = nullptr;
}

void Controller::setGamepad(Gamepad* gamepad){
    // check that reference to the gamepad exists
    if(gamepad != nullptr){
        //set the pad
        pad = gamepad;
    }
}

bool Controller::getKeyInput(int key){
    // check the that pad is set and the state is valid
    if(pad != nullptr && pad->dev.isConnected){
        //then do input
        if(pad->state.buttons[key] == GLFW_PRESS){
            return true;
        }
    }

    return false;
}

float Controller::getAxisRawInput(int key, float deadzone){
    // check the that pad is set and the state is valid
    if(pad != nullptr && pad->dev.isConnected){
        //check for positive and negative values above deadzone
        if(pad->state.axes[key] < -deadzone){
            return pad->state.axes[key];
        }else if(pad->state.axes[key] > -deadzone){
            return pad->state.axes[key];
        }
    }

    // return 0 for no input
    return 0.0f;
}

float Controller::getAxisInput(int key, float deadzone){
    // check the that pad is set and the state is valid
    if(pad != nullptr && pad->dev.isConnected){
        //check for positive and negative values above deadzone
        if(pad->state.axes[key] < -deadzone){
            return -1.0f;
        }else if(pad->state.axes[key] > deadzone){
            return 1.0f;
        }
    }

    // return 0 for no input
    return 0.0f;
}