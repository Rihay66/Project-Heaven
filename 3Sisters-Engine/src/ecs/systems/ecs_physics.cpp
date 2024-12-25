#include <ecs/systems/ecs_physics.hpp>

// include Sprite Renderer
#include "engine/physics.hpp"
#include "engine/sprite_renderer.hpp"

void ECS_Physics::registerEntity(Entity entity){
    // check if entity contains interpolation
    if((ECS::GetComponentType<Interpolation>() != 255) && ECS::CheckComponent<Interpolation>(entity)){
        // create a physics object with interpolation
        Physics::RegisterPhysicsObject(ECS::GetComponent<Transform2D>(entity), 
        ECS::GetComponent<BoxCollider2D>(entity), 
        ECS::GetComponent<Rigidbody2D>(entity), 
        ECS::GetComponent<Interpolation>(entity)
        );
        // stop function
        return;
    }

    // create a physics object without interpolation
    Physics::RegisterPhysicsObject(ECS::GetComponent<Transform2D>(entity), 
     ECS::GetComponent<BoxCollider2D>(entity), 
     ECS::GetComponent<Rigidbody2D>(entity)
    );
}

void ECS_Physics::destroyEntity(Entity entity){
    auto& transform = ECS::GetComponent<Transform2D>(entity);
    auto& collider = ECS::GetComponent<BoxCollider2D>(entity);
    auto& rb = ECS::GetComponent<Rigidbody2D>(entity);

    // destroy physics object
    Physics::DestroyPhysicsObject(transform, collider, rb);

    // destroy the entity
    ECS::DestroyEntity(entity);
}

void ECS_Physics::update(){
    for(auto const& entity : entities){
        // grab entity components
        auto& transform = ECS::GetComponent<Transform2D>(entity);
        auto& rb = ECS::GetComponent<Rigidbody2D>(entity);
        
        // check if entity has interpolation
        if((ECS::GetComponentType<Interpolation>() != 255) && ECS::CheckComponent<Interpolation>(entity)){
            auto& inter = ECS::GetComponent<Interpolation>(entity);
            // update entity
            Physics::UpdateRegisteredObject(transform, rb, inter);

            // skip iteration
            continue;
        }

        // update entity
        Physics::UpdateRegisteredObject(transform, rb);
    }
}

void ECS_Physics::renderBoxCollider(Entity entity){
    // grab entity components
    auto& transform = ECS::GetComponent<Transform2D>(entity);
    auto& boxCollider = ECS::GetComponent<BoxCollider2D>(entity);

    // render the collider
    SpriteRenderer::DrawQuadWire(transform.position + boxCollider.offset, transform.size * (boxCollider.size * glm::vec2(2.0f)), transform.rotation + boxCollider.rotationOffset, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
}

void ECS_Physics::renderAllBoxColliders(){
    for(auto const& entity : entities){
        // grab entity components
        auto& transform = ECS::GetComponent<Transform2D>(entity);
        auto& boxCollider = ECS::GetComponent<BoxCollider2D>(entity);

        // render the collider
        SpriteRenderer::DrawQuadWire(transform.position + boxCollider.offset, transform.size * (boxCollider.size * glm::vec2(2.0f)), transform.rotation + boxCollider.rotationOffset, glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
    }
}