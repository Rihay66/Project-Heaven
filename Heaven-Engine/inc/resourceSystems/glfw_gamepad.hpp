#pragma once

#ifndef GLFW_GAMEPAD_HPP
#define GLFW_GAMEPAD_HPP

// include utilities
#include <utilities/glfw_gamepad_utils.hpp>

/* An abstract Controller class which keeps track 
 of a passed gamepad. This class allows for getting
 input from the passed gamepad such as buttons and
 axes. It also sets up a callback that calls defined 
 functionality when a gamepad is diconnected. 
 !When using this class be sure to define onConnection()
*/
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

        //* getter functions

        // for getting the connection status of the gamepad
        bool getGamepadConnection();

        //* setter functions

        // for setting the gamepad to a different one
        void setGamepad(Gamepad *gamepad);

        //* helper functions

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