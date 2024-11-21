#include "../inc/test_window.hpp"
#include "ecs/systems/ecs_sprite_renderer.hpp"
#include <resourceSystems/managers/resource_manager.hpp>
#include <ecs/ecs.hpp>
#include <ecs/default_components.hpp>

TestWindow::TestWindow(int w, int h) : Window(w, h){

}

TestWindow::~TestWindow() {}

void TestWindow::init(){
    // load a texture
    ResourceManager::LoadTexture("textures/wizard1.png", "wizard");

    // load shaders
    ResourceManager::LoadShader("shaders/quad.vs", "shaders/quad.frag", nullptr, "quad");

    // initialize renderer
    SpriteRenderer::Init(ResourceManager::GetShader("quad"), glm::uvec2(20.0f));

    // init ECS
    ECS::Init();

    // register components
    ECS::RegisterComponent<Transform2D>();
    ECS::RegisterComponent<Texture2D>();
    ECS::RegisterComponent<Renderer2D>();

    // register systems
    renderer = ECS::RegisterSystem<ECS_SpriteRenderer>();

    // set signature to system
    ECS::SetSystemSignature<ECS_SpriteRenderer>(ECS::GetComponentType<Transform2D>(),
            ECS::GetComponentType<Texture2D>(), ECS::GetComponentType<Renderer2D>());

    // set camera projection
    camera.setDimensions(getWidth(), getHeight());
    camera.calculateProjectionView(ResourceManager::GetShader("quad"));

    // create a entity
    Entity entity = ECS::CreateEntity();

    ECS::AddComponent(entity, Transform2D{
        .position = glm::vec2(30.0f),
        .rotation = 0.0f,
        .size = glm::vec2(3.0f)
    });

    ECS::AddComponent(entity, Texture2D{
       .texIndex = ResourceManager::GetTextureIndex("wizard")
    });

    ECS::AddComponent(entity, Renderer2D{
        .color = glm::vec4(1.0f)
    });


}

void TestWindow::input(){

}

void TestWindow::update(){

}

void TestWindow::stepUpdate(double ts){

}

void TestWindow::render(double alpha){
    //render background
    glClearColor(0.35f, 0.35f, 0.35f, 1.0f);

    // render all entities
    renderer->render(alpha);
}
