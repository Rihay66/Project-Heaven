#pragma once

#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <string>
#include <resourceSystems/texture.hpp>
#include <resourceSystems/interpolation_utils.hpp>
#include <glm/glm.hpp>

/* Base Class that contains a modifiable transform in 2D space.
   Contains a texture index and a render type of how the texture is rendered. 
   Contains a interpolation flag that allows the object to be rendered smoothly.
*/
class GameObject{
    private:
        // contain flag that is check to see if object is interpolated
        bool interpolation;

        // define states of object to smoothly render any object
        State currentState, previousState;

        // reference to the local tag of the object
        std::string tag;

    public:
        // define enum for how to render this object
        enum class RenderType {Default = 0, flipVertically, flipHorizontal, flipBoth};

        // define variable to set how the gameObject will be renderered
        RenderType renderType;

        // transform reference of the object in 2D space
        glm::vec2 position, size;
        // visual attribute that modifies the object's texture color
        glm::vec4 color;
        // z axis object rotation 
        float rotation;
        // reference to the texture
        int textureIndex;

        //* Setter function
        
        // set GameObject's tag and changes tag in TagSystem
        void setTag(std::string tag);

        // set GameObject's current state
        void setCurrentInterpolatedState(State st);

        // set GameObject's previous state
        void setPreviousInterpolatedState(State st);

        //* Getter function

        // return the GameObject's interpolation flag
        bool getInterpolationFlag();

        // return the GameObject's current interpolated state
        State getCurrentInterpolatedState();

        // return the GameObject's previous interpolated state 
        State getPreviousInterpolatedState();

        // return the GameObject's tag
        std::string getTag();

        // constructor(s)
        GameObject(int sprt, glm::vec2 pos = glm::vec2(0.0f), glm::vec2 size = glm::vec2(1.0f), glm::vec4 color = glm::vec4(1.0f), bool interpolated = false);
};

#endif