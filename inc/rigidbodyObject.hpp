#pragma once

#ifndef RIGIDBODYOBJECT_H
#define RIGIDBODYOBJECT_H

#include "../inc/gameObject.hpp"

//declare components
struct Rigidbody{

};

struct BoxCollider{

};

//TODO: Move the components to be private in the class
class physicsObject : public GameObject{
    public:
        //reference to structs


        //constructor(s)
        physicsObject(glm::vec2 pos, float siz, int sprt, glm::vec3 color = glm::vec3(1.0f));

};

#endif