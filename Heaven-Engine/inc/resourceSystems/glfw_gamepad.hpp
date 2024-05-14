#pragma once

#ifndef GLFW_GAMEPAD_HPP
#define GLFW_GAMEPAD_HPP

#include <utilities/glfw_gamepad_utils.hpp>

//TODO: Allow for controller device reference to have modifiable variables 
// add deadzone, or other

//TODO: Provide ways user can define deadzone

class Controller {
    private:
        // storage of referece to the gamepad
        Gamepad* pad;

    public:
        // constructor
        Controller(Gamepad *gamepad);

        // deconstructor
        ~Controller();

        //* Getter functions

        //* Setter functions

        // for setting the gamepad to a different one
        void setGamepad(Gamepad *gamepad);

        //* Helper functions

        /* button callback of the gamepad which checks for the given key
         */
        bool getKeyInput(int key);

        /* axis callback of the gamepad which returns a incremental value when there is input of the given key
         */
        float getAxisRawInput(int key, float deadzone = 0.5f);

        /* axis callback of the gamepad which returns a value of direction when there is input of the given key
         */
        float getAxisInput(int key, float deadzone = 0.5f);

        /* when the pad is disconnected, the user must provide what to do within their application
        */
        virtual void onDisconnect() = 0;
};

#endif