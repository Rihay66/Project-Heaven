#include "../inc/test_window.hpp"
#include "engine/text_renderer.hpp"
#include "resourceSystems/managers/resource_manager.hpp"
#include <engine/sprite_renderer.hpp>
#include <resourceSystems/managers/sound_manager.hpp>
#include <iostream>

TestWindow::TestWindow(int w, int h) : Window(w, h){
    setTargetTimeStep(1.0f/5000.0f);
}

TestWindow::~TestWindow(){
    delete cam;
}

std::string TestWindow::GetFrameTime(){
    this->currentTime = glfwGetTime();
    this->timeDiff = this->currentTime - this->prevTime;
    this->counter++;
    if(this->timeDiff >= 1.0 / 30.0){
        //display frame per second & frame time
        std::string FPS = "" + std::to_string((1.0 / this->timeDiff) * this->counter);
        FPS = FPS.substr(0, FPS.find("."));
        this->prevTime = this->currentTime;
        this->counter = 0;
        //Return text
        frame = FPS;
    }
    return frame;
}

void TestWindow::init(){
    // init ECS
    ECS::Init();

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
    TextRenderer::Init(getWidth(), getHeight(), ResourceManager::GetShader("text"));

    // Load a sound
    SoundManager::CreateSoundCollection("test", "lofi", "sounds/lofi.wav");
    // Load another sound
    SoundManager::AddSoundToBuffer("test", "music", "sounds/music.wav");

    source.setBuffer(SoundManager::GetSoundFromBufferInColleciton("test", "lofi"));
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
    source.play(true);
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
    
    SpriteRenderer::Flush();
    
    // init the text renderer
    TextRenderer::DrawText(ResourceManager::GetFontTexture("arcade"), this->GetFrameTime(), glm::vec2(1.0f), glm::vec2(1.0f), glm::vec4(0.0f, 0.5f, 0.0f, 1.0f));
    
    //std::cout << "Quad Count: " << SpriteRenderer::stats.quadCount << "\n";
    //std::cout << "Draw Count: " << SpriteRenderer::stats.drawCount << "\n";
}