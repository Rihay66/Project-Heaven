#pragma once

#ifndef ORTHO_CAMERA_CONTROLLER_HPP
#define ORTHO_CAMERA_CONTROLLER_HPP

#include <cameras/ortho_camera.hpp>

/* deriving class of OrthoCamera with added functionality such as 
free roam keyboard driven controls with zoom, and a function to follow an object
*/
class OrthoCameraController : public OrthoCamera{
    private:
        // reference to the movement speed of the camera
        float speed;

        // reference to debug zoom 
        float zoomSpeed;

        // reference to current zoom amount
        float zoomFactor;

    public:
        // constructor
        OrthoCameraController(unsigned int Width, unsigned int Height, GLFWwindow* handle,
        Shader &shader, float cameraSpeed = 1.0f, float zoomSpeed = 1.0f);

        // destructor
        ~OrthoCameraController();

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