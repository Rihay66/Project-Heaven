#pragma once

#ifndef GLFWGAMEPAD_QUERY_UTILS_HPP
#define GLFWGAMEPAD_QUERY_UTILS_HPP

// include standard libraries
#include <sstream>

// include reference to query
#include <utilities/glfwgamepad_utils.hpp>

// TODO: Allow "glfwgamepad_utils" to grab queried devices

// define controller or gamepad keywords, expand as necessary
static const char* queryKeywords[] = {"controller", "gamepad", "playstation", "xbox", "nintendo"};

// define basic structure of a device
struct device{
    const char* name = "";
    uint8_t ID;
};

// define a list of devices
static std::vector<device> queriedDevices;

// for checking for a keyword regardless of string size
bool isKeyword(const std::string& input, const std::string& keyword) {
    std::istringstream iss(input);
    std::string token;
    while (iss >> token) {
        if (token == keyword) {
            return true; // Keyword found
        }
    }
    return false; // Keyword not found
}

//TODO: Verify that queried devices are valid by check their names
bool verifyQueriedDevice(device& d){
    // check that glfw has been initialized
    if(glfwGetError(NULL) == GLFW_NOT_INITIALIZED){
        return false; // stop function
    }

    // check that device is valid

    // grab the name of device
    char* name = const_cast<char*>(glfwGetJoystickName(d.ID));
    // lower case the name
    while(*name) {
        *name = tolower(*name);
        name++;
    }
    
    for(int i = 0; i < sizeof(queryKeywords) / sizeof(queryKeywords[0]); i++){
        // check if joystick contains a keyword
        if(isKeyword(name, queryKeywords[i])){
            // then device is a controller or gamepad

            // add device name
            d.name = name;
            
            return true;
        }
    }

    // check the name against keywords

    return false;
}

//TODO: implement controller query
// List out devices
// Verify that device is a "controller"
// Add valid devices to a resizeable list
void queryDevices(){
    // check that GLFW has been initialized
    if(glfwGetError(NULL) == GLFW_NOT_INITIALIZED){
        return; // stop function
    }

    // create local vars
    device d;
    int present;

    // loop through all available device spots
    for(uint8_t i = 0; i < GLFW_JOYSTICK_LAST; i++){
        // check each device
        present = glfwJoystickPresent(i);
        // check if device is present and verify is a valid device
        if(present == GLFW_TRUE){
            // add id to device
            d.ID = present;
            if(verifyQueriedDevice(d)){
                // the device is present and valid
                // add device to list
                queriedDevices.push_back(d);
            }
        }
    }
}



//TODO: give queried devices to query 


//TODO: Add a engine based tick that queries controllers (Move to be seperate from this file)




#endif