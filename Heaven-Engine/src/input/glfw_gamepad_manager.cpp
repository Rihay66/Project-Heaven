#include "input/glfw_gamepad.hpp"
#include <GLFW/glfw3.h>
#include <input/glfw_gamepad_manager.hpp>

// include standard library
#include <iostream>

// define static variables
std::array<std::shared_ptr<ControllerDevice>, 16>    GamepadManager::devices;

// template function 
/*
template < typename T, typename U > bool have_same_address( const T& a, const U& b ) 
{ return reinterpret_cast<const char*>( std::addressof(a) ) == reinterpret_cast<const char*>( std::addressof(b) ) ; }
*/

int GamepadManager::GetGamepadAmount(){
    return devices.size();
}

void GamepadManager::InitializeQuery(){
    // check that GLFW has not been initialized
    if(glfwGetError(NULL) == GLFW_NOT_INITIALIZED){
        return; // stop function
    }

    //TODO: Check pre-connected devices
    // check all slots for pre-connected devices
    for(int i = 0; i < GLFW_JOYSTICK_LAST; i++){
        // check if it is a gamepad and it's slot doesn't exist
        if(glfwJoystickIsGamepad(i) == GLFW_TRUE && devices.at(i) == nullptr){
            // create controller device
            devices.at(i) = std::make_shared<ControllerDevice>();
            // set the ID
            devices.at(i)->ID = i;
            // then set the connection to be true
            devices.at(i)->isConnected = true;
            //? debug
            std::cout << "Device Pre-Connected | ID: " << i << " Name: " << glfwGetGamepadName(i) << "\n";
        }
    }

    // throw ID into a connection or disconnect events
    glfwSetJoystickCallback(connectionCheck);
}

void GamepadManager::SetGamepad(Gamepad& gamepad, int index){
    //TODO: Could create a dynamic list of gamepads to be set

    //? display all devices
    for(int i = 0; i < devices.size(); i++){
        if(devices.at(i) != nullptr){
            std::cout << devices.at(i)->ID << "\n";
        }
    }

    // check index is within range and if reference already exists
    if(index < GLFW_JOYSTICK_LAST && devices.at(index) != nullptr){
        // set the reference
        gamepad.device = devices.at(index);

        //? debug
        std::cout << "Gamepad Component set to: " << devices.at(index).get() << "\n";

        return; // stop function
    }
    // else do nothing
    std::cout << "ERROR: Gamepad couldn't be set!\n";
}

void GamepadManager::UpdateGamepads(){
    // loop through available gamepads
    for(int i = 0 ; devices.size(); i++){
        if(devices.at(i) != nullptr && devices.at(i)->isConnected){
            // update state
            glfwGetGamepadState(i, &devices.at(i)->state);
        }else if(devices.at(i) == nullptr){
            return; // stop function 
        }
    }
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
    for(int i = 0; i < devices.size(); i++){
        if(devices.at(i) != nullptr && devices.at(i)->ID == jid){
            // gamepad exists, then set the connection to be true
            devices.at(i)->isConnected = true;

            //? debug
            std::cout << "Gamepad has been Re-enabled\n";

            // stop function
            return;
        }
    }

    // if ID doesn't exist then create one
    if(jid < GLFW_JOYSTICK_LAST){
        // create a new gamepad
        devices.at(jid) = std::make_shared<ControllerDevice>();
        // set the ID
        devices.at(jid)->ID = jid;
        // then set the connection to be true
        devices.at(jid)->isConnected = true;
    }
}

void GamepadManager::disableGamepad(int jid){
    // check if ID already exists
    if(devices.at(jid) != nullptr){
        // turn off device
        devices.at(jid)->isConnected = false;
    }
}