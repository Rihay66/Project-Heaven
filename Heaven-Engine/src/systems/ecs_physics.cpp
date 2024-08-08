#include <systems/ecs_physics.hpp>

void ECS_Physics::registerEntity(Entity entity){
    Physics::RegisterPhysicsObject(ECS::GetComponent<Transform2D>(entity), 
     ECS::GetComponent<BoxCollider>(entity), ECS::GetComponent<Rigidbody>(entity));
}

void ECS_Physics::update(){
    for(auto const& entity : entities){
        // grab entity components
        auto& transform = ECS::GetComponent<Transform2D>(entity);
        auto& rb = ECS::GetComponent<Rigidbody>(entity);

        // update entity
        Physics::UpdateRegisteredObject(transform, rb);
    }
}