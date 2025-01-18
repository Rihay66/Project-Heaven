#include "../inc/test_window.hpp"
#include "ecs/components/material.hpp"
#include "ecs/components/transform.hpp"
#include "ecs/systems/ecs_sprite_renderer.hpp"
#include "engine/components/interpolation.hpp"
#include <engine/sprite_renderer.hpp>
#include <resourceSystems/managers/resource_manager.hpp>
#include <engine/text_renderer.hpp>
#include <string>
#include <cstddef>
#include <chrono>

TestWindow::TestWindow() : Window(){

}

TestWindow::~TestWindow() {
    
}

std::string TestWindow::getFrameTime(){
    // Calculate and print frame rate every second
    frame = "FPS: " + std::to_string(getFrameDuration() * 1000);

    return frame;
}

void TestWindow::init(){  
    // load quad shader  
    ResourceManager::LoadShader("shaders/quad.vs", "shaders/quad.frag", nullptr, "quad");

    // load text shader
    ResourceManager::LoadShader("shaders/text.vs", "shaders/text.frag", nullptr, "text");

    // load texture
    ResourceManager::GenerateWhiteTexture();

    // load a font
    ResourceManager::LoadFontTexture("fonts/Forward.ttf", 36, "font", true);

    // Initialize camera
    camera.setDimensions(1280, 720);
    camera.calculateProjectionView(ResourceManager::GetShader("quad"));

    // init sprite renderer
    SpriteRenderer::InitQuad(ResourceManager::GetShader("quad"), {50.0f, 50.0f});

    // init text renderer
    TextRenderer::Init(1280, 720, ResourceManager::GetShader("text"));

    // init ECS
    ECS::Init();
    
    // Register components
    ECS::RegisterComponent<Transform2D>();
    ECS::RegisterComponent<Material2D>();
    ECS::RegisterComponent<Interpolation>();

    // register systems
    renderer = ECS::RegisterSystem<ECS_SpriteRenderer>();

    // set signatures
    ECS::SetSystemSignature<ECS_SpriteRenderer>(
        ECS::GetComponentType<Transform2D>(),
        ECS::GetComponentType<Material2D>()
    );

    // creat a lot of entities
    for(int x = 0; x < 80; x++){
        for(int y = 0; y < 80; y++){
            // create entity
            Entity entity = ECS::CreateEntity();

            // add components to entity, it also gets included in the ECS renderer
            ECS::AddComponent(entity,
                Transform2D{
                    .position = {x, y},
                    .rotation = 0.0f,
                    .size = {0.5f, 0.5f}
                },
                Material2D{
                    .texIndex = ResourceManager::GetTextureIndex("default")
                }
            );
        }
    }
}

void TestWindow::stepUpdate(double ts){

}

void TestWindow::update(){

}

void TestWindow::render(double alpha){
    // render background
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

    // render all entities
    renderer->render(alpha);

    // render example text
    TextRenderer::DrawText(ResourceManager::GetFontTexture("font"), getFrameTime(), 
    glm::vec2(100.0f, 200.0f), glm::vec2(1.0f), glm::vec4(0.1f, 0.8f, 0.1f, 1.0f));
}
