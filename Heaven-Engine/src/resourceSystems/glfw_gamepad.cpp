#include <resourceSystems/glfw_gamepad.hpp>

Controller* Controller::instance = nullptr;

void Controller::setInstance(Controller* inst){
    instance = inst;
}

void Controller::connectionCheck(int id, int event){
    // check that instance was set
    if(!instance)
        return;
    
    // check for connection events
    if(event == GLFW_CONNECTED){
        // call user defined function for on connection
        instance->onGamepadConnect();
    }else if(event == GLFW_DISCONNECTED){
        // call user defined function for on disconnection
        instance->onGamepadDisconnect();
    }
}

Controller::Controller(Gamepad* gamepad){
    // check that GLFW has been initialized
    if(glfwGetError(NULL) == GLFW_NOT_INITIALIZED){
        pad = nullptr; // the gamepad is undefined
    }else{
        // set the gamepad
        pad = gamepad;
        // pass the instance of this object
        setInstance(this);
        
        // set up callback of gamepad connection
        glfwSetJoystickCallback(Controller::connectionCheck);
    }
}

Controller::~Controller(){
    // clear resources and references
    this->pad = nullptr;
    setInstance(nullptr);
}

bool Controller::getGamepadConnection(){
    // check if gamepad is set and is connected
    if(pad != nullptr && pad->dev.isConnected){
        return true;
    }

    // return false, meaning gamepad is not set or is disconnected
    return false;
}

bool Controller::getGamepadState(){
    // check if gamepad is set
    if(this->pad != nullptr){
        return true; 
    }

    // return false, meaning gamepad is not set
    return false;
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