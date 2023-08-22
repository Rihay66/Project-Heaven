#pragma once

#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include <iostream>
#include <vector>

#include "../inc/rigidbodyObject.hpp"

class Physics{
    public:
        //List of all rigidbodies
        std::vector<physicsObject*> pObjs;

        //player collision offset
        const float playerOffset = 1.0f;

        //constructors / destructors
        Physics();
        ~Physics();

        //check all physics object and check the player's collision
        void CheckCollisions(physicsObject &plr);
        //Simple check for aabb collision check
        bool aabbCollision(physicsObject &a, physicsObject &b);
        //Calculate magnitude of the collision to offset the player's positiion
        float calcCollisionXMagnitude(physicsObject &a, physicsObject &b);
        float calcCollisionYMagnitude(physicsObject &a, physicsObject &b);
};

#endif