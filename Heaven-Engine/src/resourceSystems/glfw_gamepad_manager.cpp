#include <resourceSystems/glfw_gamepad_manager.hpp>

// include standard library for console display
#include <iostream>

// define static variables
std::vector<GamepadManager::gamepad> GamepadManager::queriedGamepads;

int GamepadManager::getGamepadAmount(){
    return 0;
}

void GamepadManager::updateQuery(){
    // check that GLFW has been initialized
    if(glfwGetError(NULL) == GLFW_NOT_INITIALIZED){
        return; // stop function
    }

    //TODO: Remove any gamepads that are disconnected

    // query for devices and verify device are gamepads
    queryDevices();

}

void GamepadManager::queryDevices(){
    // poll events from glfw to get all connected devices
    glfwPollEvents();

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
            // get gamepad state
            glfwGetGamepadState(pad.dev.ID, &pad.state);
            //? Debug print of gamepad
            std::cout << "Gamepad Name: " << pad.dev.name << " | ID: " << pad.dev.ID << "\n";
            // add device to list
            queriedGamepads.push_back(pad);
        }
        
    }

    //? Debug print amount of gamepads present
    std::cout << "Amount of Gamepads present: " << queriedGamepads.size() << "\n";

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

