#pragma once

#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include <iostream>
#include <vector>
#include <math.h>

#include "../inc/rigidbodyObject.hpp"

//include box2d lib
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>

class b2World;

class Physics{
    private:
        //List of different rigidbody's with either a trigger or non trigger flag
        std::vector<physicsObject*> triggerObjs;
        std::vector<physicsObject*> rigidbodyObjs;

    public:
        //List of all rigidbodies
        std::vector<physicsObject*> pObjs;

        //reference to physics world
        b2World* world = nullptr;

        //constructors / destructors
        Physics();
        ~Physics();
        //Init function that is used after adding all pObjs
        void init(glm::vec2 gravity = glm::vec2(0.0f, 9.81f));

        //check all physics object and check the player's collision
        void CheckCollisions(physicsObject &plr);
        //Simple check for aabb collision check
        bool aabbCollision(physicsObject &a, physicsObject &b);

        //Make a enum translate between box2d and rigidbodyObject class
        static b2BodyType RbToB2Types(BodyType bodyType){
            
            switch(bodyType){
                case BodyType::Static:  return b2_staticBody;
                case BodyType::Dynamic: return b2_dynamicBody;
                case BodyType::Kinematic: return b2_kinematicBody;
            }

            //No type was set or there is a unknown body type being passed
            std::cout << "Warning:Unknown RB Body Type being passed!" << "\n";
            return b2_staticBody;
        }
};

#endif