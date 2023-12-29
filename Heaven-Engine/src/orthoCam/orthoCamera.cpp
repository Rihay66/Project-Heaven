#include <orthoCam/orthoCamera.hpp>

Camera::Camera(unsigned int Width, unsigned int Height, GLFWwindow* handle, Shader &shader) : 
width(Width), height(Height), window(handle), shader(shader){  
    //update shader
    calculateProjectionView();    

    //tell shader to set view
    this->shader.SetMatrix4("projectionView", this->projectionView);
}

Camera::~Camera(){
}

void Camera::calculateProjectionView()
{
    this->projection = glm::ortho(0.0f, static_cast<float>(this->width), 
        0.0f, static_cast<float>(this->height), -1.0f, 1.0f);

    glm::mat4 transform = glm::translate(glm::mat4(1.0f), this->position) * glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0,0,1));

    this->view = glm::inverse(transform);

    //put together the projectionView
    this->projectionView = this->projection * this->view;
}