#pragma once

#ifndef GLFW_GAMEPAD_QUERY_UTILS_HPP
#define GLFW_GAMEPAD_QUERY_UTILS_HPP

// include standard libraries
#include <vector>

// include utilities
#include <utilities/glfw_gamepad_utils.hpp>

/* A static singleton GamepadManager class that hosts 
 several functions to query for connected or disconnected 
 Gamepads. Each obtained connected controller are stored for
 reference to allow for further usage of the gamepad.
 This class keeps track of all connected or diconnected 
 devices. 
*/
class GamepadManager{
    public:
        //* getter functions

        // returns the number of devices that identify as "Gamepads"
        static int getGamepadAmount();

        // returns a gamepad reference at the determined index, default gets the first gamepad
        static Gamepad* getGamepad(int index = 0);

        //* helper functions

        // to update the query of devices, parameter is used for debugging or setting
        static void updateQuery(char option = 'n');

        // to update the state of all gamepads, regardless of the flag 'isConnected'
        static void updateGamepadsState();

        // to remove any disconnected devices 
        static void removeDisconnectedDevices();

        // to clear any used resources
        static void clear();

    private:
        // private resource storage

        // define a list of devices that are gamepads
        static std::vector<Gamepad> queriedGamepads;

        // private constructor, that is to avoid any actual gamepad manager objects
        GamepadManager() {}

        //* private helper functions

        /* list out devices
         verify that device is a "controller"
         add valid devices to storage
        */
        static void queryDevices();

        // checks each connected device and sets their 'isConnection' flag to false if by state is disconnected
        static void checkGamepadConnection();

        // returns the state of existance of a ID within the list of gamepads
        static bool checkGamepadExistance(int id);
};

#endif