#include <systems/ecs_sprite_renderer.hpp>

// include standard components
#include <ecs/default_components.hpp>

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