#pragma once

#ifndef ORTHOCAMERA_HPP
#define ORTHOCAMERA_HPP

#include <resourceSys/shader.hpp>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

// Camera class
class Camera{
    protected:
        // declare const vars
        const glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        const glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);

        // maxtrix variable to be used to calculate the 
        glm::mat4 projection, view, projectionView, transform;

        // reference to the window size
        unsigned int width, height;

        // reference to the GLFW window handle
        GLFWwindow* window;

    public:
        // reference to the camera position
        glm::vec3 position = glm::vec3(0.0f);

        // reference to the shader that can be changed at anytime
        Shader shader;

        // construcotr
        Camera(unsigned int width, unsigned int height, GLFWwindow* handle,
        Shader &shader);

        // destructor
        ~Camera();

        // does calculations of the view and projection to create the ProjectionView
        virtual void calculateProjectionView();
};

#endif