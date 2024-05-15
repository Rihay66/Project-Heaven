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

        // storage of controller reference
        static Controller* instance;

        // sets the static instance 
        static void setInstance(Controller* inst);

        // joystick callback that calls virtual functions depending on an event 
        static void connectionCheck(int id, int event);

    public:
        // constructor
        Controller(Gamepad *gamepad);

        // deconstructor
        ~Controller();

        //* Getter functions

        // for getting the connection status of the gamepad
        bool getGamepadConnection();

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

        /* when the pad is connected, the user must provide what to do within their application
        */
        virtual void onGamepadConnect() = 0;

        /* when the pad is disconnected
        */
        virtual void onGamepadDisconnect() {};
};

#endif