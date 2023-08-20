#pragma once

#ifndef RIGIDBODYOBJECT_H
#define RIGIDBODYOBJECT_H

#include "../inc/gameObject.hpp"

//future use for changing sprite 
//* used for physics detection
enum Direction{
    UP, DOWN, LEFT, RIGHT
};

class physicsObject : public GameObject{
    public:
        //reference to state of the object
        //Used to check if object is enabled and when disabled is automatically removed from game
        bool isDestroyed; 
        //Used to check 
        bool isTrigger;

        //constructor(s)
        physicsObject(glm::vec2 pos, glm::vec2 siz, int sprt, bool destroyed = false, bool trigger = false, glm::vec3 color = glm::vec3(1.0f));

        //Used to define any function to do when this object is triggered
        //* Used only when 'isTrigger' is enabled
        virtual void triggerCollision(){}
};

#endif