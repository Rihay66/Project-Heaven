#pragma once

#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include <vector>

#include "../inc/rigidbodyObject.hpp"

class physics{
    public:
        //List of all rigidbodies
        std::vector<physicsObject*> pObjs;

        //player collision offset
        const float playerOffset = 1.0f;

        //constructors / destructors
        physics();
        ~physics();

        //check all physics object and check the player's collision
        void CheckCollisions(physicsObject &plr);
        //Simple check for aabb collision check
        bool aabbCollision(physicsObject &a, physicsObject &b);
};

#endif