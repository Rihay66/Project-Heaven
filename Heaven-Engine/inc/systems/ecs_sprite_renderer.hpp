#pragma once

#ifndef ECS_SPRITE_RENDERER_HPP
#define ECS_SPRITE_RENDERER_HPP

// include ECS
#include <ecs/ecs.hpp>

// include Engine Renderer
#include <engine/sprite_renderer.hpp>

/* ECS_SpriteRenderer class is a ECS system that
 allows entities with the necessary components to 
 be rendered using the SpriteRenderer static class
*/
class ECS_SpriteRenderer : public System{
    public:
        // render all entities added
        void render(double alpha);
};

// create an aliasto easily refer to this system
using ECS_2DRenderer = std::shared_ptr<ECS_SpriteRenderer>;

#endif