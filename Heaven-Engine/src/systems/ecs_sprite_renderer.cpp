#include <systems/ecs_sprite_renderer.hpp>

// include standard components
#include <ecs/default_components.hpp>

ECS_SpriteRenderer::ECS_SpriteRenderer(){
    // initialize ECS
    ECS::Init();

    // register components
    ECS::RegisterComponent<Transform2D>();
    ECS::RegisterComponent<Texture2D>();
    ECS::RegisterComponent<Renderer2D>();
}

void ECS_SpriteRenderer::registerComponents(){
    // create signature
    Signature sig;
    sig.set(ECS::GetComponentType<Transform2D>());
    sig.set(ECS::GetComponentType<Texture2D>());
    sig.set(ECS::GetComponentType<Renderer2D>());

    // register signature to system
    ECS::SetSystemSignature<ECS_SpriteRenderer>(sig);
}

void ECS_SpriteRenderer::render(double alpha){
    // loop through all entities
    for(auto const& entity : entities){
        // Grab entity components
        auto& transform = ECS::GetComponent<Transform2D>(entity);
        auto& texture = ECS::GetComponent<Texture2D>(entity);
        auto& render = ECS::GetComponent<Renderer2D>(entity);

        // add to stack
        SpriteRenderer::Stack(texture.texIndex, transform.position, transform.scale, transform.rotation, render.color);
    }

    // flush
    SpriteRenderer::Flush();
}