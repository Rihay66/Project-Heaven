#pragma once

#ifndef ORTHOCAMERACONTROLLER_HPP
#define ORTHOCAMERACONTROLLER_HPP

#include <orthoCam/orthoCamera.hpp>

// deriving class of OrthoCamera with 
class CameraController : public Camera{
    private:
        // reference to the movement speed of the camera
        float speed;

        // reference to debug zoom 
        float zoomSpeed;

        // reference to current zoom amount
        float zoomFactor;

    public:
        // constructor
        CameraController(unsigned int Width, unsigned int Height, GLFWwindow* handle,
        Shader &shader, float cameraSpeed = 1.0f, float zoomSpeed = 1.0f);

        // destructor
        ~CameraController();

        // overwrite projectionview calculation function
        void calculateProjectionView() override;

        //* virtual functions

        // virtual function that sets the camera position to snap to a given position
        virtual void followPos(glm::vec2 pos, glm::vec2 size = glm::vec2(0.0f),
        glm::vec2 offset = glm::vec2(0.0f));

        //virtual function that allows for keyboard controlled camera movement using WASD and zooming with up and down arrow keys
        virtual void inputMovement(float deltatime);
};

#endif