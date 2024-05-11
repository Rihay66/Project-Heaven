#pragma once

#ifndef GLFWGAMEPAD_QUERY_UTILS_HPP
#define GLFWGAMEPAD_QUERY_UTILS_HPP

// include standard libraries
#include <vector>

// include GLFW
#include <GLFW/glfw3.h>

static const char* queryKeywords[] = {"controller", "gamepad", "playstation", "xbox", "nintendo", "4"};

//TODO: Define a controller, has an ID, active, 

//TODO: define Heaven-Engine buttons for Xbox, Playstation, and even switch

//TODO: grab queried devices from query 

//TODO: implement controller reference
// have devices have unique ID to allow for GLFW input
// have a call back that reference GLFW input 

//TODO: Allow for controller device reference to have modifiable variables 
// add deadzone, or other

class GamepadManager{
    public:
        // define basic structure of a device
        struct device{
            const char* name = "";
            int ID;
        };

        // define structure of a gamepad
        struct gamepad{
            device dev;
            // define gamepad state holder, used to further verify gamepads
            GLFWgamepadstate state;
            // variables
        };

        //* Getter functions

        // returns the number of devices that identify as "Gamepads"
        static int getGamepadAmount();

        //* Helper functions

        // to update the query of devices
        static void updateQuery();

    private:
        // private resource storage

        // define a list of devices that are gamepads
        static std::vector<gamepad> queriedGamepads;

        //private constructor, that is to avoid any actual gamepad manager objects
        GamepadManager() {}

        //* Private Helper functions

        /* List out devices
         Verify that device is a "controller"
         Add valid devices to a resizeable list
        */
        static void queryDevices();

        // returns the state of existance of a ID within the list of gamepads
        static bool checkGamepadExistance(int id);
};

#endif