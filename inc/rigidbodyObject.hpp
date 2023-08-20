#pragma once

#ifndef RIGIDBODYOBJECT_HPP
#define RIGIDBODYOBJECT_HPP

#include "../inc/gameObject.hpp"

//future use for changing sprite 
//* used for physics detection
enum Direction{
    UP, DOWN, LEFT, RIGHT
};

//TODO: Make box collider component to define the collider size and offset from the gameobject's position and size

class physicsObject : public GameObject{
    public:
        //reference to state of the object
        //Used to check if object is enabled and when disabled is automatically removed from game
        bool isDestroyed; 
        //Used to check 
        bool isTrigger;

        //constructor(s)
        physicsObject(glm::vec2 pos, glm::vec2 siz, int sprt, glm::vec3 color = glm::vec3(1.0f), bool destroyed = false, bool trigger = false);

        //Used to define any function to do when this object is triggered
        //* Used only when 'isTrigger' is enabled
        virtual void triggerCollision(){}
};

#endif