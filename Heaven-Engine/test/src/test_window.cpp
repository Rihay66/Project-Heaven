#include "../inc/test_window.hpp"
#include "cameras/ortho_camera.hpp"
#include "resourceSystems/resource_manager.hpp"
#include <engine/sprite_renderer.hpp>
#include <engine/physics.hpp>
#include <engine/sound_manager.hpp>
#include <iostream>

TestWindow::TestWindow(int w, int h) : Window(w, h){

}

TestWindow::~TestWindow(){

}

void TestWindow::init(){
    // Load a shader
    ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.frag", nullptr, "test");

    // set up camera
    cam = new OrthoCamera(this->getWidth(), getHeight(), ResourceManager::GetShader("test"));

    // Load a texture
    ResourceManager::LoadTexture("textures/default.png", "test", true);

    // init the renderer
    SpriteRenderer::Init(ResourceManager::GetShader("test"), glm::uvec2(30.0f));

    // Create a sound source
    source = new SoundSource();

    // Load a sound
    SoundManager::CreateSoundCollection("test", "lofi", "sounds/lofi.wav");

    source->setBuffer(SoundManager::GetSoundFromBufferInColleciton("test", "lofi"));

    // init physics
    Physics::Init();
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
    // play sound
    source->play(true);
}

void TestWindow::render(double alpha){

    //render background
    glClearColor(0.35f, 0.35f, 0.35f, 1.0f);
    // render 
    SpriteRenderer::Stack(ResourceManager::GetTexture("test"), glm::vec2(4.0f, 2.5f), glm::vec2(1.1f), 0.0f);
    SpriteRenderer::Stack(ResourceManager::GetTexture("test"), glm::vec2(2.0f, 2.0f), glm::vec2(1.0f), 0.0f);
    
    SpriteRenderer::Flush();
    
    //std::cout << "Quad Count: " << SpriteRenderer::stats.quadCount << "\n";
    //std::cout << "Draw Count: " << SpriteRenderer::stats.drawCount << "\n";
}