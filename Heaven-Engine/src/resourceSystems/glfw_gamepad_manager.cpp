#include <resourceSystems/glfw_gamepad_manager.hpp>

// include standard library for console display
#include <iostream>

// define static variables
std::vector<GamepadManager::gamepad> GamepadManager::queriedGamepads;

int GamepadManager::getGamepadAmount(){
    return 0;
}

void GamepadManager::updateQuery(char option){
    //TODO: include the option to add debug options

    // check that GLFW has been initialized
    if(glfwGetError(NULL) == GLFW_NOT_INITIALIZED){
        return; // stop function
    }

    // poll events from glfw to get all connected devices
    glfwPollEvents();

    // query for new devices and verify device are gamepads
    queryDevices();

    // check any disconnected devices by state
    checkGamepadConnection();
}

void GamepadManager::removeDisconnectedDevices(){
    // remove any devices that have a 'disconnected' flag and by state is disconnected
}

void GamepadManager::clear(){
    // clear resources
}

void GamepadManager::queryDevices(){
    // loop through all possible joysticks
    for(int i = 0; i < GLFW_JOYSTICK_LAST; i++){
        // check each joystick if they're present
        if(glfwJoystickIsGamepad(i) == GLFW_TRUE){
            // check if gamepad already exists, if yes then skip this joystick
            if(checkGamepadExistance(i))
                continue; // skip iteration
            
            // create a gamepad
            gamepad pad;
            pad.dev.ID = i;
            pad.dev.name = glfwGetGamepadName(i);
            //! By default device is set to be connected
            pad.isConnected = true;
            // get gamepad state
            glfwGetGamepadState(pad.dev.ID, &pad.state);
            //? Debug print of gamepad
            std::cout << "Gamepad Name: " << pad.dev.name << " | ID: " << pad.dev.ID << "\n";
            // add device to list
            queriedGamepads.push_back(pad);
        }
    }
}

void GamepadManager::checkGamepadConnection(){
    // loop through all available gamepads
    for(int i = 0; i < queriedGamepads.size(); i++){
        // check their connection 
        if(glfwGetGamepadState(queriedGamepads.at(i).dev.ID, &queriedGamepads.at(i).state) == GLFW_FALSE && queriedGamepads.at(i).isConnected){
            // if no connection then set 'isConnected' flag to false
            queriedGamepads.at(i).isConnected = false;

            //? debug print
            std::cout << "Gamepad Name: " << queriedGamepads.at(i).dev.name << " | ID: " << queriedGamepads.at(i).dev.ID << " has been disconnected\n"; 
        }else if(glfwGetGamepadState(queriedGamepads.at(i).dev.ID, &queriedGamepads.at(i).state) != GLFW_FALSE && !queriedGamepads.at(i).isConnected){
            // there is a reconnection then set 'isConnected' flag to true
            queriedGamepads.at(i).isConnected = true;

            //? debug print
            std::cout << "Gamepad Name: " << queriedGamepads.at(i).dev.name  << " | ID: " << queriedGamepads.at(i).dev.ID << " has been reconnected\n";
        }
    }
}

bool GamepadManager::checkGamepadExistance(int id){
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

