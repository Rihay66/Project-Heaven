#include <cameras/ortho_camera_controller.hpp>

OrthoCameraController::OrthoCameraController(unsigned int Width, unsigned int Height, GLFWwindow* handle, Shader &shader, float cameraSpeed, float zoomAmount)
 : OrthoCamera(Width, Height, handle, shader), speed(cameraSpeed), zoomSpeed(zoomAmount), zoomFactor(0.0f){}

OrthoCameraController::~OrthoCameraController(){}

void OrthoCameraController::calculateProjectionView()
{
    // include zzoom factor to the orthographic projection
    this->projection = glm::ortho(0.0f + zoomFactor / 2, static_cast<float>(this->width) - zoomFactor / 2, 
        0.0f + zoomFactor, static_cast<float>(this->height) - zoomFactor, -1.0f, 1.0f);

    // set up the transform 
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), this->position) * glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0,0,1));

        // set up the view using the inverse of the transform
    this->view = glm::inverse(transform);

    // put together the projectionView
    this->projectionView = this->projection * this->view;
    // tell shader to set projectionView
    this->shader.SetMatrix4("projectionView", this->projectionView, true);
}

void OrthoCameraController::followPos(glm::vec2 pos, glm::vec2 size, glm::vec2 offset){
    // follow a position
    this->position = glm::vec3((((pos.x + offset.x) * size.x) - this->width / 2.0f), (((pos.y + offset.y) * size.y) - this->height / 2.0f), 0.0f);
}

void OrthoCameraController::inputMovement(float deltaTime){

    // calculate movement using the speed and delta time
    float movement = speed * deltaTime;

    // when window can't be found
    if(window == nullptr){
        // stop function
        return;
    }

    // input for increase movement while holding key
    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
        movement *= 3.0f;
    }

    // input for movement
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        // move up
        position += movement * up * 3.0f;
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        // move down
        position -= movement * up * 3.0f;
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        // move left
        position -= movement * right;
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        // move right
        position += movement * right;
    }

    // input for zooming in
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
        // zoom in 
        zoomFactor += zoomSpeed;
    }
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
        // zoom out
        zoomFactor -= zoomSpeed;
    }

    // check to make sure zoom is only for zooming out and avoid inverting the projection
    if(zoomFactor >= 0.0f)
        zoomFactor = 0.0f;
}