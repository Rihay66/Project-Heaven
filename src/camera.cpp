#include "../inc/camera.hpp"

Camera::Camera(unsigned int Width, unsigned int Height, Shader &shader, float cameraSpeed) : speed(cameraSpeed), width(Width), height(Height){
    this->shader = shader;
    
    //update shader
    calculateProjectionView();    

    //tell shader to set view
    this->shader.SetMatrix4("projectionView", this->projectionView);
}

Camera::~Camera(){
}

void Camera::follow(glm::vec2 pos, glm::vec2 size){
    //follow a position
    this->position = glm::vec3((pos.x + size.x / 2.0f) - this->width / 2.0f, (pos.y + size.y / 2.0f) - this->height / 2.0f, 0.0f);
    //update shader
    calculateProjectionView();

    //tell shader to set view
    this->shader.SetMatrix4("projectionView", this->projectionView);
}

//TODO: Add a zoom input using the scroll wheel
void Camera::camInput(float deltaTime, GLFWwindow* &window){

    float movement = speed * deltaTime;

    //input for movement
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        //move up
        position -= movement * up * 2.0f;
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        //move down
        position += movement * up * 2.0f;
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
    calculateProjectionView();

    //tell shader to set view
    this->shader.SetMatrix4("projectionView", this->projectionView);
}
void Camera::calculateProjectionView()
{
    this->projection = glm::ortho(0.0f, static_cast<float>(this->width), 
        static_cast<float>(this->height), 0.0f, -1.0f, 1.0f);

    glm::mat4 transform = glm::translate(glm::mat4(1.0f), this->position) * glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0,0,1));

    this->view = glm::inverse(transform);

    //put together the projectionView
    this->projectionView = this->projection * this->view;
}
