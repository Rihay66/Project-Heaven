#pragma once

#ifndef ECS_PHYSICS_HPP
#define ECS_PHYSICS_HPP

// include ECS
#include <ecs/ecs.hpp>

// include Engine Physics
#include <engine/physics.hpp>

class ECS_Physics : public System{
    public:
        // to register the entity's components, if already stored then it is skipped
        void registerEntity(Entity entity);

        // update all registered entities
        void update();

        //* debug functions

        // draw the box collider of given entity
        void renderBoxCollider(Entity entity);

        // draw all the box colliders of all entites
        void renderAllBoxColliders();
};

// create alias to easily refer to this system
using ECS_PhysicsPtr = std::shared_ptr<ECS_Physics>;

#endif
