#pragma once

#ifndef GLFW_OBSERVER_HPP
#define GLFW_OBSERVER_HPP

// include standard library
#include <inttypes.h>
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
        //* observe functions

        // create a demo window of ImGUI
        static void ObserveDemo();

        /* create an observation with a name and countinous parameters of primative types
        * NOTE: Default components can be also included
        */
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

        ///* helper functions

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
            }else if constexpr(std::is_same_v<T, glm::vec3>){
                // add vec3 observation
                glm::vec3& temp = t;
                ImGui::Text("X: %.3f Y: %.3f Z: %.3f", temp.x, temp.y, temp.z);
            }else if constexpr(std::is_same_v<T, glm::vec4>){
                // add vec4 observation
                glm::vec4& temp = t;
                ImGui::Text("X: %.3f Y: %.3f Z: %.3f W: %.3f", temp.x, temp.y, temp.z, temp.w);
            }else if constexpr(std::is_same_v<T, Transform2D>){
                Transform2D& temp = t;
                ImGui::Text("Transform2D");
                // print each value
                ImGui::Text("\tPosition");
                ImGui::Text("\t\tX: %.3f Y: %.3f", temp.position.x, temp.position.y);
                ImGui::Text("\tRotation");
                ImGui::Text("\t\t%.3f", temp.rotation);
                ImGui::Text("\tSize");
                ImGui::Text("\t\tX: %.3f Y: %.3f", temp.size.x, temp.size.y);
            }else if constexpr(std::is_same_v<T, Texture2D>){
                Texture2D& temp = t;
                ImGui::Text("Texture2d");
                // print each value
                ImGui::Text("\tTexIndex");
                ImGui::Text("\t\t%d", temp.texIndex);
                ImGui::Text("\tTexCoords");
                for(glm::vec2& i : temp.texCoords){
                    ImGui::Text("\t\tX: %.3f Y: %.3f", i.x, i.y);
                }
            }else if constexpr(std::is_same_v<T, Renderer2D>){
                Renderer2D& temp = t;
                ImGui::Text("Renderer2D");
                // print each value
                ImGui::Text("\tColor");
                ImGui::Text("\t\tR: %.3f G: %.3f B: %.3f A: %.3f", temp.color.x, temp.color.y, temp.color.z, temp.color.w);
            }else if constexpr(std::is_same_v<T, Rigidbody>){
                Rigidbody& temp = t;
                ImGui::Text("Rigidbody");
                // print each value
                ImGui::Text("\tBodyType");
                // check body type
                switch (temp.Type) {
                    case BodyType::Static:
                        ImGui::Text("\t\tStatic");
                        break;
                    case BodyType::Dynamic:
                        ImGui::Text("\t\tDynamic");
                        break;
                    case BodyType::Kinematic:
                        ImGui::Text("\t\tKinematic");
                        break;
                    default:
                        break;
                }
                ImGui::Text("\tFixedRotation");
                ImGui::Text("\t\t%s", temp.fixedRotation ? "true" : "false");
                //? print out the runtime body memory address
                ImGui::Text("\tRuntimeBody");
                ImGui::Text("\t\t%p", temp.runtimeBody);
            }else if constexpr(std::is_same_v<T, BoxCollider>){
                BoxCollider& temp = t;
                ImGui::Text("BoxCollider");
                // print each value
                ImGui::Text("\tOffset");
                ImGui::Text("\t\tX: %.3f Y: %.3f", temp.offset.x, temp.offset.y);
                ImGui::Text("\tSize");
                ImGui::Text("\t\tX: %.3f Y: %.3f", temp.size.x, temp.size.y);
                ImGui::Text("\tRotationOffset");
                ImGui::Text("\t\t%.3f", temp.rotationOffset);
                ImGui::Text("\tDensity");
                ImGui::Text("\t\t%.3f", temp.density);
                ImGui::Text("\tFriction");
                ImGui::Text("\t\t%.3f", temp.friction);
                ImGui::Text("\tRestitution");
                ImGui::Text("\t\t%.3f", temp.restitution);
                ImGui::Text("\tRestitutionThreshold");
                ImGui::Text("\t\t%.3f", temp.restitutionThreshold);
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