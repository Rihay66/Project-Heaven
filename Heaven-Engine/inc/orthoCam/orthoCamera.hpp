#pragma once

#ifndef ORTHOCAMERA_HPP
#define ORTHOCAMERA_HPP

#include <resourceSys/shader.hpp>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

//Camera class
class Camera{
    public:
        //declare const vars
        const glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        const glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);

        //delcare projection var
        glm::mat4 projection;
        glm::mat4 view;
        glm::mat4 projectionView;

        //reference to the camera position
        glm::vec3 position = glm::vec3(0.0f);

        //reference to the shader that can be changed at anytime
        Shader shader;

        //reference to the GLFW window handle
        GLFWwindow* window;

        //reference to the window size
        unsigned int width, height;

        //Construcotr
        Camera(unsigned int Width, unsigned int Height, GLFWwindow* handle,
        Shader &shader);

        //Destructor
        ~Camera();

        //Does multiplication of the view and projection to create the ProjectionView
        virtual void calculateProjectionView();
};

#endif