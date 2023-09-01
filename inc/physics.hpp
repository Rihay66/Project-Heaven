#pragma once

#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include <iostream>
#include <vector>
#include <math.h>

#include "../inc/rigidbodyObject.hpp"

class Physics{
    private:
        //List of different rigidbody's with either a trigger or non trigger flag
        std::vector<physicsObject*> triggerObjs;
        std::vector<physicsObject*> rigidbodyObjs;

    public:
        //List of all rigidbodies
        std::vector<physicsObject*> pObjs;

        //constructors / destructors
        Physics();
        ~Physics();
        //Init function that is used after adding all pObjs
        void init(glm::vec2 gravity = glm::vec2(0.0f, 9.81f));

        //check all physics object and check the player's collision
        void CheckCollisions(physicsObject &plr);
        //Simple check for aabb collision check
        bool aabbCollision(physicsObject &a, physicsObject &b);
};

#endif