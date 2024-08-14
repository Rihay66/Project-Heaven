#pragma once

#ifndef ORTHO_CAMERA_HPP
#define ORTHO_CAMERA_HPP

#include <resourceSystems/shader.hpp>
#include <glm/glm.hpp>

/* Orthographic Camera class used for allowing 
 perception of what's being rendered in a Orthographic
 manner, the class can be modified and changed to allow
 desired perception of the scene.  
*/
class OrthoCamera{
    protected:
        // declare const vars
        const glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        const glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);

        // maxtrix variable to be used to calculate the 
        glm::mat4 projection, view, projectionView, transform;

        // reference to the window size
        unsigned int width, height;

    public:
        // reference to the camera position
        glm::vec3 position = glm::vec3(0.0f);

        // construcotr
        OrthoCamera(unsigned int width, unsigned int height);

        // destructor
        ~OrthoCamera();

        //TODO: Add setter and getters for setting the height and width, and maybe other vars

        //* helper functions

        // does calculations of the view and projection to create the ProjectionView and set to given shader
        virtual void calculateProjectionView(Shader& shader);
};

#endif