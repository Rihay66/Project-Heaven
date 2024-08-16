#pragma once

#ifndef GLFW_OBSERVER_HPP
#define GLFW_OBSERVER_HPP

// include standard library
#include <map>

// include ImGUI

/* A static singleton
*/
class Observer {
    public:
        //* overload functions

        //* helper functions

        // initialize ImGUI and the Observer for use
        static void Init();

        // render all observed values
        static void Render();

    private:
        // private constructor
        Observer() {}

        // properly de-allocates all loaded resources
        static void clear();

        //! Currently EXPERIMENTAL, may cause exceptions or segfaults
        // private boolean to track automatic clear()
        static bool isAutoClearSet;
        // set up automatic de-allocation of loaded resources
        static void setUpAutoClear();
};

#endif