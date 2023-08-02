#pragma once

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "../inc/renderer.hpp"

class GameObject{
    public:
        //transform reference of the object
        glm::vec2 position, size;
        glm::vec3 color;
        float rotation;
        //state of the object
        bool destroyed;
        bool collidable;
        //reference to the shader
        Texture2D sprite;

        //constructor(s)
        GameObject();
        GameObject(glm::vec2 pos, glm::vec2 size, Texture2D sprt, glm::vec3 color = glm::vec3(1.0f));

        //draw sprite
        virtual void Draw2D(Renderer* &renderer);
};

#endif