#pragma once

#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include <iostream>
#include <vector>
#include <math.h>

#include "../inc/rigidbodyObject.hpp"

class Physics{
    public:
        struct OverlapInfo{
            float yOverlap;
            float xOverlap; 
        };

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
        OverlapInfo calcCollisionMagnitude(physicsObject &a, physicsObject &b);
};

#endif