#include <resourceSystems/managers/glfw_gamepad_manager.hpp>

// include standard library
#include <iostream>

// define static variables
std::vector<Gamepad> GamepadManager::queriedGamepads;

int GamepadManager::GetGamepadAmount(){
    return queriedGamepads.size();
}

Gamepad* GamepadManager::GetGamepad(int index){
    // check if index is within range
    if(index >= 0 && index < queriedGamepads.size()){
        return &queriedGamepads.at(index);
    }

    // couldn't find the gamepad
    return nullptr;
}

void GamepadManager::UpdateQuery(char option){
    //TODO: include the option to add debug options

    // check that GLFW has been initialized
    if(glfwGetError(NULL) == GLFW_NOT_INITIALIZED){
        return; // stop function
    }

    // query for new devices and verify device are gamepads
    QueryDevices();

    // check any disconnected devices by state
    CheckGamepadConnection();
}

void GamepadManager::UpdateGamepadsState(){
    // check that GLFW has been initialized
    if(glfwGetError(NULL) == GLFW_NOT_INITIALIZED){
        return; // stop function
    }

    // loop through all gamepads and update their state
    for(int i = 0; i < queriedGamepads.size(); i++){
        // get gamepad state regardless of the flag 'isConnected'
        glfwGetGamepadState(queriedGamepads.at(i).dev.ID, &queriedGamepads.at(i).state);
    }
}

void GamepadManager::RemoveDisconnectedDevices(){
    // remove any devices that have a 'isConnected' flag set to be false and by state is disconnected
    
    // loop through all current gamepads
    for(int i = 0; i < queriedGamepads.size(); i++){
        // check for the flag and state
        if(!queriedGamepads.at(i).dev.isConnected && glfwGetGamepadState(queriedGamepads.at(i).dev.ID, &queriedGamepads.at(i).state) == GLFW_FALSE){
            auto index = queriedGamepads.begin() + i;
            queriedGamepads.erase(index);
        }
    }
}

void GamepadManager::QueryDevices(char option){
    // loop through all possible joysticks
    for(int i = 0; i < GLFW_JOYSTICK_LAST; i++){
        // check each joystick if they're present
        if(glfwJoystickIsGamepad(i) == GLFW_TRUE){
            // check if gamepad already exists, if yes then skip this joystick
            if(CheckGamepadExistance(i))
                continue; // skip iteration
            
            // create a gamepad
            Gamepad pad;
            pad.dev.ID = i;
            pad.dev.name = glfwGetGamepadName(i);
            //! By default device is set to be connected
            pad.dev.isConnected = true;
            // get gamepad state
            glfwGetGamepadState(pad.dev.ID, &pad.state);
            //? Debug print of gamepad
            std::cout << "Gamepad Name: " << pad.dev.name << " | ID: " << pad.dev.ID << "\n";
            // add device to list
            queriedGamepads.push_back(pad);
        }
    }
}

void GamepadManager::CheckGamepadConnection(){
    // loop through all available gamepads
    for(int i = 0; i < queriedGamepads.size(); i++){
        // check their connection 
        if(glfwGetGamepadState(queriedGamepads.at(i).dev.ID, &queriedGamepads.at(i).state) == GLFW_FALSE && queriedGamepads.at(i).dev.isConnected){
            // if no connection then set 'isConnected' flag to false
            queriedGamepads.at(i).dev.isConnected = false;

            //? debug print
            std::cout << "Gamepad Name: " << queriedGamepads.at(i).dev.name << " | ID: " << queriedGamepads.at(i).dev.ID << " has been disconnected\n"; 
        }else if(glfwGetGamepadState(queriedGamepads.at(i).dev.ID, &queriedGamepads.at(i).state) != GLFW_FALSE && !queriedGamepads.at(i).dev.isConnected){
            // there is a reconnection then set 'isConnected' flag to true
            queriedGamepads.at(i).dev.isConnected = true;

            //? debug print
            std::cout << "Gamepad Name: " << queriedGamepads.at(i).dev.name  << " | ID: " << queriedGamepads.at(i).dev.ID << " has been reconnected\n";
        }
    }
}

bool GamepadManager::CheckGamepadExistance(int id){
    // check given id if it exists within list of "queriedGamepads"
    for(int i = 0; i < queriedGamepads.size(); i++){
        if(queriedGamepads.at(i).dev.ID == id){
            // given id already exists
            return true;
        }
    }

    // given id doesn't exists within queried gamepads
    return false;
}

