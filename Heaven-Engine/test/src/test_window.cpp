#include "../inc/test_window.hpp"
#include <resourceSystems/resource_manager.hpp>
#include <engine/physics.hpp>

TestWindow::TestWindow(int w, int h) : Window(w, h){

}

TestWindow::~TestWindow(){

}

void TestWindow::init(){
    // Load a shader
    ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.frag", nullptr, "test");

    // init physics
    Physics::init();
}

void TestWindow::input(){
    // check for escape key to exit window
    if(glfwGetKey(this->getWindowHandle(), GLFW_KEY_ESCAPE) == GLFW_PRESS){
        // exit window
        glfwSetWindowShouldClose(this->getWindowHandle(), true);
    }
}

void TestWindow::update(){

}

void TestWindow::stepUpdate(double ts){

}

void TestWindow::render(double alpha){

    //render background
    glClearColor(0.35f, 0.35f, 0.35f, 1.0f);
}