#include <input/glfw_gamepad_manager.hpp>

// include standard library
#include <iostream>

// define static variables
std::vector<Gamepad>                        GamepadManager::queriedGamepads;
std::array<std::shared_ptr<Gamepad>, 16>    GamepadManager::gamepads;

int GamepadManager::GetGamepadAmount(){
    return queriedGamepads.size();
}

void GamepadManager::InitializeQuery(){
    // check that GLFW has not been initialized
    if(glfwGetError(NULL) == GLFW_NOT_INITIALIZED){
        return; // stop function
    }

    //TODO: Check pre-connected devices

    // throw ID into a connection or disconnect events
    glfwSetJoystickCallback(connectionCheck);
}

void GamepadManager::connectionCheck(int jid, int event){
    // check event type
    if(event == GLFW_CONNECTED){
        //? debug
        std::cout << "Device Connected | ID: " << jid << " Name: " << glfwGetGamepadName(jid)<< "\n";

        // create or enable a gamepad
        enableGamepad(jid);
    }else if(event == GLFW_DISCONNECTED){
        //? debug
        std::cout << "Device Disconnected | ID: " << jid << "\n";
        // disable a gamepad
        disableGamepad(jid);
    }  
}

void GamepadManager::enableGamepad(int jid){
    // check if ID already exists
    for(int i = 0; i < gamepads.size(); i++){
        if(queriedGamepads.at(i).ID == jid){
            // gamepad exists, then set the connection to be true
            queriedGamepads.at(i).isConnected = true;

            //? debug
            std::cout << "Gamepad has been Re-enabled\n";

            // stop function
            return;
        }
    }

    // if ID doesn't exist then create one
    
    // create new gamepad

}

void GamepadManager::disableGamepad(int jid){
    // check if ID already exists
}