#pragma once

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "../inc/texture.hpp"
#include <glm/glm.hpp>

class GameObject{
    public:
        //transform reference of the object
        glm::vec2 position;
        glm::vec3 color;
        float size;
        float rotation;
        //reference to the texture
        int textureIndex;

        //constructor(s)
        GameObject(glm::vec2 pos, float size, int sprt, glm::vec3 color = glm::vec3(1.0f));
};

#endif