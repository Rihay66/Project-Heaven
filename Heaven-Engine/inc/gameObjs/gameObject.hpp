#pragma once

#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include "../inc/texture.hpp"
#include <glm/glm.hpp>

//TODO: Make a tag system for base game objects and have a global storage of the tag only for gameobjects and deriving classes

class GameObject{
    public:
        //future use for changing sprite 
        enum Direction{
            UP, DOWN, LEFT, RIGHT
        };

        //transform reference of the object
        glm::vec2 position;
        glm::vec3 color;
        glm::vec2 size;
        float rotation;
        //reference to the texture
        int textureIndex;

        //constructor(s)
        GameObject(glm::vec2 pos, glm::vec2 size, int sprt, glm::vec3 color = glm::vec3(1.0f));
};

#endif