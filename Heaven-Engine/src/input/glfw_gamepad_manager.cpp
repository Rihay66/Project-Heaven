#include "input/glfw_gamepad.hpp"
#include <input/glfw_gamepad_manager.hpp>

// include standard library
#include <iostream>
#include <memory>

// define static variables
std::vector<GamepadManager::PreferencePad> GamepadManager::prefGamepads;
std::array<std::shared_ptr<Gamepad>, 16>    GamepadManager::gamepads;

// template function 
template < typename T, typename U > bool have_same_address( const T& a, const U& b ) 
{ return reinterpret_cast<const char*>( std::addressof(a) ) == reinterpret_cast<const char*>( std::addressof(b) ) ; }

int GamepadManager::GetGamepadAmount(){
    return prefGamepads.size();
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

void GamepadManager::SetGamepad(Gamepad& gamepad, int index){
    // check if reference already exists
    for(int i = 0; i < prefGamepads.size(); i++){
        if(have_same_address(prefGamepads.at(i).gamepad, gamepad)){
            // change ID preference of that existing pad


            return; // stop function
        }
    }

    // add gamepad reference to the manager and that it needs reference to the index(aka ID)
    PreferencePad pad;
    pad.preferedIndex = index;
    pad.gamepad = &gamepad;

    //? display their address
    std::cout << &gamepad << "\n";
    std::cout << pad.gamepad << "\n";

    // add preference pad to pref gamepads
    prefGamepads.push_back(pad);
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
        if(gamepads.at(i) != nullptr && gamepads.at(i)->ID == jid){
            // gamepad exists, then set the connection to be true
            gamepads.at(i)->isConnected = true;

            //? debug
            std::cout << "Gamepad has been Re-enabled\n";

            // stop function
            return;
        }
    }

    // if ID doesn't exist then create one
    if(jid < GLFW_JOYSTICK_LAST){
        // create a new gamepad
        gamepads.at(jid) = std::make_shared<Gamepad>();
        // set the ID
        gamepads.at(jid)->ID = jid;
        // then set the connection to be true
        gamepads.at(jid)->isConnected = true;
    }
}

void GamepadManager::disableGamepad(int jid){
    // check if ID already exists
}