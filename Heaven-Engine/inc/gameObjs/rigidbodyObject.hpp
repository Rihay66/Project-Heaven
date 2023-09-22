#pragma once

#ifndef RIGIDBODYOBJECT_HPP
#define RIGIDBODYOBJECT_HPP

#include "../inc/gameObject.hpp"
#include <box2d/b2_body.h>

enum class BodyType {Static = 0, Dynamic, Kinematic };

//physics components
struct Rigidbody{
    BodyType Type = BodyType::Dynamic;
    bool fixedRotation = false;

    //storage for runtime
    void* runtimeBody = nullptr;
    //Constructors
    Rigidbody() = default;
    Rigidbody(const Rigidbody&) = default;
};

struct BoxCollider
{
    glm::vec2 offset = {0.0f, 0.0f};
    glm::vec2 size = {0.5f, 0.5f};
    float rotationOffset = 0.0f;

    float density = 1.0f;
    float friction = 0.5f;
    float restitution = 0.0f;
    float restitutionThreshold = 0.5f;

    //storage for runtime
    void* runtimeBody = nullptr;

    //constructors
    BoxCollider() = default;
    BoxCollider(const BoxCollider&) = default;
};

class physicsObject : public GameObject{
    public:
        //Declare direction of the object
        Direction dir;

        //Declare Rigidbody
        Rigidbody rb;
        //declare BoxCollider
        BoxCollider collider;

        //Used to check if object is enabled and when disabled is automatically removed from game
        bool isDestroyed; 
        //Used to check 
        bool isTrigger;

        //constructor(s)
        physicsObject(glm::vec2 pos, glm::vec2 siz, int sprt, glm::vec3 color = glm::vec3(1.0f), bool destroyed = false, bool trigger = false);

        //Used to define any function to do when this object is triggered
        //* Used only when 'isTrigger' is enabled
        virtual void triggerCollision(){}

        //Used to define to make changes to the b2 body and returns b2Body*
        virtual b2Body* physicBody(){return (b2Body*)rb.runtimeBody;}
};

#endif