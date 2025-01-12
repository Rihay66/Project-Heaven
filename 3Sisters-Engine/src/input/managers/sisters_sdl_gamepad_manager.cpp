#include <input/managers/sisters_sdl_gamepad_manager.hpp>

#include <cstdlib>
#include <SDL3/SDL.h>

//? include IO for debug prints
#include <iostream>

using namespace SDL;

// define static variables
std::vector<GamepadManager::QueuedGamepad>              GamepadManager::queuedGamepads;
std::array<std::shared_ptr<ControllerDevice>, 15>       GamepadManager::devices;
SDL_Event*                                              GamepadManager::eventHandle = nullptr;
bool                                                    GamepadManager::isAutoClearSet = false;

void GamepadManager::InitializeQuery(SDL_Event& event){
    // check if SDL hasn't been initialized
    if(!SDL_WasInit(SDL_INIT_GAMEPAD | SDL_INIT_JOYSTICK)){
        std::cout << "ERROR: SDL is not initialized!\n";
        return; // stop functions 
    }

    // set the event handle 
    eventHandle = &event;
}

int GamepadManager::GetGamepadAmount(){
    // init var to contain actual amount of devices available
    int amount = 0;

    for(int i = 0; i < 15; i++){
        if(devices.at(i) != nullptr){
            amount++;
        }else{
            break; // stop loop
        }
    }

    return amount;
}

void GamepadManager::SetGamepad(Gamepad& gamepad, int index){
    // set auto clear
    setUpAutoClear();

    // check index is within range and if reference already exists
    if(index < 15 && devices.at(index) != nullptr){
        // set the reference
        gamepad.device = devices.at(index);

        return; // stop function
    }else if(index < 15 && devices.at(index) == nullptr){
        // queue the given gamepad
        
        QueuedGamepad qp;
        qp.index = index;
        qp.gamepad = &gamepad;

        // add to queue
        queuedGamepads.push_back(qp);
    }
}

void GamepadManager::PollIO(){
    // check if the event handle is set meaning, there is intention of using the gamepad system
    if(eventHandle == nullptr){
        return; // stop functions
    }

    // check if SDL and event handle hasn't been initialized
    if(!SDL_WasInit(SDL_INIT_GAMEPAD | SDL_INIT_JOYSTICK)){
        std::cout << "ERROR: SDL is not initialized!\n";
        return; // stop functions
    }

    // check for events
    switch(eventHandle->type){
        case SDL_EVENT_GAMEPAD_ADDED:
            // call for enable gamepad with the correspoding device
            enableGamepad(eventHandle->cdevice.which);

            break;
        case SDL_EVENT_GAMEPAD_REMOVED:
            // disable the gamepad that was removed
            disableGamepad(eventHandle->cdevice.which);

            break;
        default:
            break;
    }
}


void GamepadManager::enableGamepad(int jid){
    // check if ID already exists
    for(int i = 0; i < GetGamepadAmount(); i++){
        if(devices.at(i)->ID == jid){
            // gamepad exists, then set the connection to be true
            devices.at(i)->isConnected = true;

            // attempt to reopen
            devices.at(jid)->controller = SDL_OpenGamepad(jid);

            // stop function
            return;
        }
    }

    // if ID doesn't exist then create one
    if(jid < 15){
        // create a new gamepad
        devices.at(jid) = std::make_shared<ControllerDevice>();
        // set the ID
        devices.at(jid)->ID = jid;
        // then set the connection to be true
        devices.at(jid)->isConnected = true;
        // then set the game controller
        devices.at(jid)->controller = SDL_OpenGamepad(jid);

        // loop in reverse through queued up gamepads that need to be set
        for(int i = 0; i < queuedGamepads.size(); i++){
            if(queuedGamepads.at(i).index == jid && queuedGamepads.at(i).gamepad != nullptr){
                // set the gamepad
                queuedGamepads.at(i).gamepad->device = devices.at(jid);
                
                // remove from list
                queuedGamepads.erase(queuedGamepads.begin() + i);
            }
        }
    }
}

void GamepadManager::disableGamepad(int jid){
    // check for given ID which device was removed and properly close it
    for(int i = 0; i < GetGamepadAmount(); i++){
        // check which device matches the given id
        if(SDL_GetJoystickID(SDL_GetGamepadJoystick(devices.at(i)->controller)) == jid){
            // properly close the device
            devices.at(i)->isConnected = false;
            SDL_CloseGamepad(devices.at(i)->controller);

            return; // stop function
        }
    }
    
}

void GamepadManager::clear(){
    // de-allocate resources

    // remove all reference of queued gamepads
    for(QueuedGamepad& pad : queuedGamepads){
        pad.gamepad = nullptr;
    }

    // close all created SDL joysticks
    for(int i = 0; i < GetGamepadAmount(); i++){
        SDL_CloseGamepad(devices.at(i)->controller);
    }
}

void GamepadManager::setUpAutoClear(){
    // set up on exit to call the Clear()
    if(!isAutoClearSet && std::atexit(clear) == 0){
        isAutoClearSet = true; // disable calling this function again
    }
}