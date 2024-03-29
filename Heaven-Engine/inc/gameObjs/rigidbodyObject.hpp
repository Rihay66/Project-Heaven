#pragma once

#ifndef RIGIDBODYOBJECT_HPP
#define RIGIDBODYOBJECT_HPP

#include <gameObjs/gameObject.hpp>
#include <resourceSys/componentUtils.hpp>
#include <box2d/b2_body.h>

class PhysicsObject : public GameObject{
    public:
        //Declare Rigidbody
        Rigidbody rb;
        //declare BoxCollider
        BoxCollider collider;

        //Used to check if object is enabled and when disabled is automatically removed from game
        bool isDestroyed; 

        //constructor(s)
        PhysicsObject(int sprt, glm::vec2 pos = glm::vec2(0.0f), glm::vec2 siz = glm::vec2(1.0f), glm::vec4 color = glm::vec4(1.0f), bool interpolation = true, bool destroyed = false);

        //Used to define to make changes to the b2 body and returns b2Body*
        virtual b2Body* physicBody(){return (b2Body*)rb.runtimeBody;}
};

#endif