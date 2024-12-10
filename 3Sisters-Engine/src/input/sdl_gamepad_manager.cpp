#include <input/sdl_gamepad_manager.hpp>

#include <cstdlib>
#include <SDL2/SDL.h>

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
    if(SDL_WasInit(SDL_INIT_GAMECONTROLLER) == 0){
        std::cout << "ERROR: SDL is not initialized!\n";
        return; // stop functions 
    }

    // set the event handle 
    eventHandle = &event;

    // check all slots for pre-connected device
    for(int i = 0; i < 15; i++){
        // check if slot is a game controller and it's slot doesn't exist
        if(SDL_IsGameController(i) == SDL_TRUE && devices.at(i) == nullptr){
            // create controller device

            //set id

            // set connection to be true

            // set the game controller
        }
    }
    
}

void GamepadManager::PollIO(){
    // check if SDL and event handle hasn't been initialized
    if(SDL_WasInit(SDL_INIT_GAMECONTROLLER) == 0){
        std::cout << "ERROR: SDL is not initialized!\n";
        return; // stop functions
    }else if(eventHandle == nullptr){
        std::cout << "ERROR: SDL event handle is not set!\n";
        return; // stop functions
    }

    // check for events
    switch(eventHandle->type){
        case SDL_CONTROLLERDEVICEADDED:
            // check which device it was

            // call for enable gamepad with the appropriate index
            
            break;
        case SDL_CONTROLLERDEVICEREMOVED:
            // check which device it was

            // disable the gamepad

            break;
        default:
            break;
    }
}


void GamepadManager::enableGamepad(int jid){
    // check if ID already exists
    for(int i = 0; i < devices.size(); i++){
        if(devices.at(i) != nullptr && devices.at(i)->ID == jid){
            // gamepad exists, then set the connection to be true
            devices.at(i)->isConnected = true;

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
    // check if ID already exists
    if(devices.at(jid) != nullptr){
        // turn off device
        devices.at(jid)->isConnected = false;
    }
}

void GamepadManager::clear(){
    // de-allocate resources
}

void GamepadManager::setUpAutoClear(){
    // set up on exit to call the Clear()
    if(!isAutoClearSet && std::atexit(clear) == 0){
        isAutoClearSet = true; // disable calling this function again
    }
}