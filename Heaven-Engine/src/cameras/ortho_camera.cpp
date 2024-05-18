#include <cameras/ortho_camera.hpp>

OrthoCamera::OrthoCamera(unsigned int w, unsigned int h,  Shader &shdr) : 
width(w), height(h), shader(shdr){  
    // update projection and add to shader
    calculateProjectionView();
}

OrthoCamera::~OrthoCamera(){}

void OrthoCamera::calculateProjectionView(){
    // create the projection
    this->projection = glm::ortho(0.0f, static_cast<float>(this->width), 
        0.0f, static_cast<float>(this->height), -1.0f, 1.0f);

    // set up the transform 
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), this->position) 
    * glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0,0,1));

    // set up the view using the inverse of the transform
    this->view = glm::inverse(transform);

    // put together the projectionView
    this->projectionView = this->projection * this->view;
    // tell shader to set projectionView
    this->shader.SetMatrix4("projectionView", this->projectionView, true);
}