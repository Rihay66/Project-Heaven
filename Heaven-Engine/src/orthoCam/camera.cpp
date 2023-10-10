#include <orthoCam/camera.hpp>

Camera::Camera(unsigned int Width, unsigned int Height, Shader &shader, float cameraSpeed, float zoomAmount) : speed(cameraSpeed), zoomAmount(zoomAmount),width(Width), height(Height), zoomFactor(0){
    this->shader = shader;
    
    //update shader
    calculateProjectionView();    

    //tell shader to set view
    this->shader.SetMatrix4("projectionView", this->projectionView);
}

Camera::~Camera(){
}

void Camera::follow(glm::vec2 pos, glm::vec2 size){
    //reset zoom factor
    this->zoomFactor = 0.0f;

    //follow a position
    this->position = glm::vec3(((pos.x * size.x) - this->width / 2.0f) + size.x / 2.0f, ((pos.y * size.y) - this->height / 2.0f) + size.y / 2.0f, 0.0f);
    //update shader
    calculateProjectionView();

    //tell shader to set view
    this->shader.SetMatrix4("projectionView", this->projectionView);
}

//TODO: Add a zoom input using the scroll wheel
void Camera::camInput(float deltaTime, GLFWwindow* &window){

    float movement = speed * deltaTime;

    //input for increase movement while holding key
    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
        movement *= 3.0f;
    }

    //input for movement
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        //move up
        position += movement * up * 3.0f;
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        //move down
        position -= movement * up * 3.0f;
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        //move left
        position -= movement * right;
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        //move right
        position += movement * right;
    }

    //input for zooming in
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
        //zoom in 
        zoomFactor += zoomAmount;
    }
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
        //zoom out
        zoomFactor -= zoomAmount;
    }

    //Check to make sure zoom is only for zooming out and not to zoom
    if(zoomFactor >= 0.0f)
        zoomFactor = 0.0f;

    //update shader
    calculateProjectionView();

    //tell shader to set view
    this->shader.SetMatrix4("projectionView", this->projectionView);
}

void Camera::calculateProjectionView()
{
    this->projection = glm::ortho(0.0f + zoomFactor / 2, static_cast<float>(this->width) - zoomFactor / 2, 
        0.0f + zoomFactor, static_cast<float>(this->height) - zoomFactor, -1.0f, 1.0f);

    glm::mat4 transform = glm::translate(glm::mat4(1.0f), this->position) * glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0,0,1));

    this->view = glm::inverse(transform);

    //put together the projectionView
    this->projectionView = this->projection * this->view;
}