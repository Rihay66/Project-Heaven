#pragma once

#ifndef ECS_SPRITE_RENDERER_HPP
#define ECS_SPRITE_RENDERER_HPP

//TODO: ECS sprite renderer is a wrapper for the sprite renderer with ECS implementation

#include <ecs/ecs.hpp>

#include <engine/sprite_renderer.hpp>

class ECS_SpriteRenderer : public System{
    private:

    public:
        // constructor
        ECS_SpriteRenderer();

        // further register components
        void registerComponents();

        //TODO: Allow for rendering with linear interpolation

        // render all entities added
        void render(double alpha);
};

#endif