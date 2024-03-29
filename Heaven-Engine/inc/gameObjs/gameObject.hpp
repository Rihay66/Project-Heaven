#pragma once

#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <string>
#include <resourceSys/texture.hpp>
#include <resourceSys/interpolationUtil.hpp>
#include <glm/glm.hpp>

class GameObject{
    private:
        //Contain flag that is check to see if object is interpolated
        bool interpolation;

    public:
        //Define enum for how to render this object
        enum class RenderType {Default = 0, flipVertically, flipHorizontal, flipBoth};

        //Define states of object to smoothly render any object
        State currentState, previousState;

        //Define variable to set how the gameObject will be renderered
        RenderType renderType;

        //reference to the local tag
        std::string tag;

        //transform reference of the object
        glm::vec2 position;
        glm::vec4 color;
        glm::vec2 size;
        float rotation;
        //reference to the texture
        int textureIndex;

        //Getter function

        //Return the GameObject's interpolation flag
        bool getInterpolationFlag();

        //constructor(s)
        GameObject(int sprt, glm::vec2 pos = glm::vec2(0.0f), glm::vec2 size = glm::vec2(1.0f), glm::vec4 color = glm::vec4(1.0f), bool interpolated = false);
};

#endif