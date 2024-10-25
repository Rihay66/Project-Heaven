#include <cameras/ortho_camera.hpp>

void OrthoCamera::setDimensions(unsigned int w, unsigned int h){
    this->width = w;
    this->height = h;
}

void OrthoCamera::setWidth(unsigned int w){
    this->width = w;
}

void OrthoCamera::setHeight(unsigned int h){
    this->height = h;
}

unsigned int OrthoCamera::getWidth(){
    return this->width;
}

unsigned int OrthoCamera::getHeight(){
    return this->height;
}

void OrthoCamera::calculateProjectionView(Shader& shader){
    // create the projection
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->width), 
        0.0f, static_cast<float>(this->height), -1.0f, 1.0f);

    // set up the view by inversing the transform 
    glm::mat4 view = glm::inverse(glm::translate(glm::mat4(1.0f), this->position) 
    * glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0,0,1)));

    // put together the projectionView
    this->projectionView = projection * view;

    // tell shader to set projectionView
    shader.SetMatrix4("projectionView", this->projectionView, true);
}