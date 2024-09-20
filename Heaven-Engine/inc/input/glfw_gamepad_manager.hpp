#pragma once

#ifndef GLFW_GAMEPAD_MANAGER_HPP
#define GLFW_GAMEPAD_MANAGER_HPP

// include standard libraries
#include <array>
#include <vector>
#include <memory>

#include <input/glfw_gamepad.hpp>

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
        static int GetGamepadAmount();

        //* helper functions

        // set query event callback, expands a list of connected and disconnected devices
        static void InitializeQuery();

        /* add a gamepad reference that can be filled from the list of queried gamepads
        * NOTE: By default picks the first gamepad
        */
        static void SetGamepad(Gamepad& gamepad, int index = 0);

        /*
        */
        static void UpdateGamepads();

    private:

        // define prefered index along with a reference gamepad
        struct PreferencePad{
            unsigned int preferedIndex = 0;
            Gamepad* gamepad = nullptr;
        };

        // private resource storage

        // define a list to store reference of given unset gamepads that can be queried and set
        static std::vector<PreferencePad> prefGamepads;
        // define a list of gamepads detected by GLFW
        static std::array<std::shared_ptr<Gamepad>, 16> gamepads;
 
        // private constructor, that is to avoid any actual gamepad manager objects
        GamepadManager() {}

        //* private helper functions

        // glfw callback to check connection of a gamepad
        static void connectionCheck(int jid, int event); 

        // create a gamepad reference to be used on connection
        static void enableGamepad(int jid);

        // disable gamepad reference when disconnected
        static void disableGamepad(int jid);
};

#endif