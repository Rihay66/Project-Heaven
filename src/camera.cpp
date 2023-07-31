#include "../inc/camera.h"

Camera::Camera(unsigned int Width, unsigned int Height, Shader &shader, float cameraSpeed) : speed(cameraSpeed){
    this->shader = shader;
    //update shader
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0,0,1));

    glm::mat4 view = glm::inverse(transform);

    //tell shader to set view
    shader.SetMatrix4("view", view);
}

Camera::~Camera(){
}

void Camera::follow(glm::vec3 position){
    //follow a position
}

void Camera::camInput(float deltaTime, GLFWwindow* window){

    float movement = speed * deltaTime;

    //input for movement
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        //move up
        position -= movement * up;
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        //move down
        position += movement * up;
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        //move left
        position -= movement * right;
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        //move right
        position += movement * right;
    }

    //update shader
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0,0,1));

    glm::mat4 view = glm::inverse(transform);

    //tell shader to set view
    shader.SetMatrix4("view", view);
}