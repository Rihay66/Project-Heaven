#pragma once

#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <resourceSys/shader.hpp>
#include <glm/glm.hpp>

//TODO: Move this camera to be it's own object and have a camera controller that includes all the input

//Camera class
class Camera{
    private:
        //declare const vars
        const glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
        const glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);
        //delcare projection var
        glm::mat4 projection;
        glm::mat4 view;
        glm::mat4 projectionView;

        //Does multiplication of the view and projection to create the ProjectionView
        void calculateProjectionView();

        //reference to the camera position
        glm::vec3 position = glm::vec3(0.0f);
        //reference to the shader that will update it's view value
        Shader shader;
        //reference to the movement speed of the camera
        float speed;
        //reference to the window size
        unsigned int width, height;
        //reference to debug zoom 
        float zoomAmount;
    public:
        //Construcotr
        Camera(unsigned int Width, unsigned int Height, 
        Shader &shader, float cameraSpeed = 1.0f, float zoomAmount = 1.0f);

        //Destructor
        ~Camera();

        //input
        void camInput(float deltaTime);
        //follow a position
        void follow(glm::vec2 = glm::vec3(0.0f), glm::vec2 size = glm::vec3(0.0f));

        //reference to a modifiable zoom factor
        float zoomFactor;
};

#endif