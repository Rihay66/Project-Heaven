#pragma once

#ifndef ORTHO_CAMERA_HPP
#define ORTHO_CAMERA_HPP

// include GLM
#include <glm/glm.hpp>

// include shader
#include <resourceSystems/resource_shader.hpp>

/* Orthographic Camera class is used for allowing 
 perception of what's being rendered in a Orthographic
 manner. The class can be modified and changed to allow
 desired perception of the scene. 
 ! Requires a shader class and width and height
*/
class OrthoCamera{
    protected:
        // storage for the projection view of a orthographic projection
        glm::mat4 projectionView;

        // reference to the window size
        unsigned int width = 0, height = 0;

    public:
        // reference to the camera's position
        glm::vec2 position = glm::vec3(0.0f);

        //* setter functions
        
        // set both the width and height
        void setDimensions(unsigned int w, unsigned int h);

        // set the width
        void setWidth(unsigned int w);
        
        // set the height
        void setHeight(unsigned int h);

        //* getter functions

        // get the width
        unsigned int getWidth();

        // get the height
        unsigned int getHeight();

        //* helper functions

        // does calculations of the view and projection to create the ProjectionView and set to given shader
        virtual void calculateProjectionView(Shader& shader);
};

#endif