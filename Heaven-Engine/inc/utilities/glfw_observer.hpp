#pragma once

#ifndef GLFW_OBSERVER_HPP
#define GLFW_OBSERVER_HPP

// include GLFW
#include <GLFW/glfw3.h>

// include ImGUI
#include "imgui.h"

/* A static singleton
*/
class Observer {
    public:
        //* overload functions

        // create a demo window of ImGUI
        static void ObserveDemo();

        template<typename... Args>
        void Observe(const char* name, Args... args){
            // create the window with given name
            ImGui::Begin(name);

            // loop through all arguments to be added to window


            // end window creation 
            ImGui::End();
        }

        //* helper functions

        // initialize ImGUI and the Observer for use
        static void Init(GLFWwindow* handle);

        // start a new frame to render ImGUI windows
        static void BeginObservations();


        // render all observed values
        static void Render();

    private:
        // private resource

        // track if certain functions were called to allow functionality
        static bool isFrameCreated;

        // private constructor
        Observer() {}

        // check the given type and display value in ImGUI
        template<typename T>
        void CheckType(T& t){
            // check type
            
        }

        // properly de-allocates all loaded resources
        static void clear();

        //! Currently EXPERIMENTAL, may cause exceptions or segfaults
        // private boolean to track automatic clear()
        static bool isAutoClearSet;
        // set up automatic de-allocation of loaded resources
        static void setUpAutoClear();
};

#endif