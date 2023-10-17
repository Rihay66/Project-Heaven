#pragma once

#ifndef ORTHOCAMERACONTROLLER_HPP
#define ORTHOCAMERACONTROLLER_HPP

#include <orthoCam/orthoCamera.hpp>

//Deriving class of OrthoCamera
class CameraController : public Camera{
    public:
        //reference to the movement speed of the camera
        float speed;
        //reference to debug zoom 
        float zoomSpeed;

        //reference to current zoom amount
        float zoomFactor;

        //Constructor
        CameraController(unsigned int Width, unsigned int Height, GLFWwindow* handle,
        Shader &shader, float cameraSpeed = 1.0f, float zoomSpeed = 1.0f);

        //Destructor
        ~CameraController();

        //overwrite projectionview calculation function
        void calculateProjectionView() override;

        //Overridable functions
        virtual void followPos(glm::vec2 pos, glm::vec2 size = glm::vec2(0.0f),
        glm::vec2 offset = glm::vec2(0.0f));
        virtual void inputMovement(float deltatime);
};

#endif