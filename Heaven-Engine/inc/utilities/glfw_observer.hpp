#pragma once

#ifndef GLFW_OBSERVER_HPP
#define GLFW_OBSERVER_HPP

// include standard library
#include <type_traits>

// include GLFW
#include <GLFW/glfw3.h>

// include ImGUI
#include <imgui.h>

// include default components
#include <ecs/default_components.hpp>

/* A static singleton
*/
class Observer {
    public:
        //* overload functions

        // create a demo window of ImGUI
        static void ObserveDemo();

        // create an observation with a name and countinous parameters of primative types
        template<typename... Args>
        static void Observe(const char* name, Args&... args){
                // check if frame wasn't created
                if(!isFrameCreated)
                    return; // stop function

            // create the window with given name
            ImGui::Begin(name);

            // loop through all arguments to be added to window
            (CheckType(args), ...);

            // end window creation 
            ImGui::End();
        }

        //* helper functions

        // initialize ImGUI and the Observer for use
        static void Init(GLFWwindow* handle);

        // start a new frame to render ImGUI windows
        static void NewObservations();

        // render all observed values
        static void FlushObservations();

    private:
        // private resource

        // track if certain functions were called to allow functionality
        static bool isFrameCreated;

        // private constructor
        Observer() {}

        // check the given type and display value in ImGUI
        template<typename T>
        static void CheckType(T& t){
            //TODO: Find a cleaner way to check for the type
            
            // check type
            if constexpr(std::is_same_v<T, float>){
                // add float observation
                ImGui::Text("Float: %.2f", t);
            }else if constexpr(std::is_same_v<T, bool>){
                // add boolean observation
                ImGui::Text("Boolean: %s", t ? "true" : "false");
            }else if constexpr(std::is_same_v<T, int>){
                // add integer observation
                ImGui::Text("Int: %d", t);
            }else if constexpr(std::is_same_v<T, glm::vec2>){
                // add vec2 observation
                glm::vec2& temp = t;
                ImGui::Text("X: %.3f Y: %.3f", temp.x, temp.y);
            }else if constexpr(std::is_same_v<T, Transform2D>){
                Transform2D& temp = t;
                ImGui::Text("Transform2D");
                // use recursion to print each value 
                ImGui::Text("\tPosition");
                ImGui::Text("\t\tX: %.3f Y: %.3f", temp.position.x, temp.position.y);
                ImGui::Text("\tRotation");
                ImGui::Text("\t\t%.3f", temp.rotation);
                ImGui::Text("\tSize");
                ImGui::Text("\t\tX: %.3f Y: %.3f", temp.size.x, temp.size.y);
            }
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