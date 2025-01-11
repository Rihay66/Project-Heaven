#include "../inc/test_window.hpp"
#include "ecs/components/material.hpp"
#include "ecs/components/transform.hpp"
#include "ecs/systems/ecs_sprite_renderer.hpp"
#include "engine/components/interpolation.hpp"
#include <engine/sprite_renderer.hpp>
#include <resourceSystems/managers/resource_manager.hpp>

TestWindow::TestWindow() : Window(){

}

TestWindow::~TestWindow() {
    
}

void TestWindow::init(){  
    // load quad shader  
    ResourceManager::LoadShader("shaders/quad.vs", "shaders/quad.frag", nullptr, "quad");

    // load texture
    ResourceManager::GenerateWhiteTexture();

    // Initialize camera
    camera.setDimensions(1280, 720);
    camera.calculateProjectionView(ResourceManager::GetShader("quad"));

    // init sprite renderer
    SpriteRenderer::InitQuad(ResourceManager::GetShader("quad"), {50.0f, 50.0f});

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

    // create entity
    Entity entity = ECS::CreateEntity();

    // add components to entity, it also gets included in the ECS renderer
    ECS::AddComponent(entity,
        Transform2D{
            .position = {12.5f, 7.0f},
            .rotation = 0.0f,
            .size = {3.0f, 3.0f}
        },
        Material2D{
            .texIndex = ResourceManager::GetTextureIndex("default")
        }
    );
}

void TestWindow::stepUpdate(double ts){
    // grab entity, assume entity ID is 0
    auto& transform = ECS::GetComponent<Transform2D>(0);
    // rotate the entity
    transform.rotation += 100.0f * ts;
}

void TestWindow::update(){

}

void TestWindow::render(double alpha){
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

    // render stuff
    renderer->render(alpha);
}
