#include "../inc/test_window.hpp"
#include "engine/text_renderer.hpp"
#include "gameObjects/physics_object.hpp"
#include "resourceSystems/resource_manager.hpp"
#include <engine/sprite_renderer.hpp>
#include <engine/physics.hpp>
#include <engine/sound_manager.hpp>
#include <iostream>

TestWindow::TestWindow(int w, int h) : Window(w, h){
    setTargetTimeStep(1.0f/5000.0f);
}

TestWindow::~TestWindow(){

}

std::string TestWindow::GetFrameTime(){
    this->currentTime = glfwGetTime();
    this->timeDiff = this->currentTime - this->prevTime;
    this->counter++;
    if(this->timeDiff >= 1.0 / 30.0){
        //display frame per second & frame time
        std::string FPS = "" + std::to_string((1.0 / this->timeDiff) * this->counter);
        int pos = FPS.find(".");
        FPS = FPS.substr(0, pos);
        this->prevTime = this->currentTime;
        this->counter = 0;
        //Return text
        frame = FPS;
    }
    return frame;
}

void TestWindow::init(){
    // Load a shader
    ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.frag", nullptr, "test");
    ResourceManager::LoadShader("shaders/text.vs", "shaders/text.frag", nullptr, "text");

    // set up camera
    cam = new OrthoCamera(this->getWidth(), getHeight(), ResourceManager::GetShader("test"));

    // Load a texture
    ResourceManager::LoadTexture("textures/default.png", "test", true);

    // Load a font
    ResourceManager::LoadFontTexture("fonts/Arcade.ttf", 36, "arcade", false);

    // init the renderer
    SpriteRenderer::Init(ResourceManager::GetShader("test"), glm::uvec2(30.0f));

    // init the text renderer
    text = new TextRenderer(getWidth(), getHeight(), ResourceManager::GetShader("text"));

    // Create a sound source
    source = new SoundSource();

    // Load a sound
    SoundManager::CreateSoundCollection("test", "lofi", "sounds/lofi.wav");

    source->setBuffer(SoundManager::GetSoundFromBufferInColleciton("test", "lofi"));

    // init physics
    Physics::Init(glm::vec2(0.0f));
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
    //update physics
    //Physics::UpdateWorld(ts);
    //Physics::UpdatePhysics();
    // play sound
    source->play(true);
}

void TestWindow::render(double alpha){

    //render background
    glClearColor(0.35f, 0.35f, 0.35f, 1.0f);


    // render 
    for(int x = 0; x < 100; x++){
        for(int y = 0; y < 100; y++){
            // stack quads
            SpriteRenderer::Stack(ResourceManager::GetTexture("test"), glm::vec2(x, y), glm::vec2(0.5f), 0.0f);
        }
    }

    //SpriteRenderer::Flush();

    text->drawText(ResourceManager::GetFontTexture("arcade"), this->GetFrameTime(), glm::vec2(1.0f), glm::vec2(1.0f), glm::vec4(0.0f, 0.5f, 0.0f, 1.0f));
    
    //std::cout << "Quad Count: " << SpriteRenderer::stats.quadCount << "\n";
    //std::cout << "Draw Count: " << SpriteRenderer::stats.drawCount << "\n";
}