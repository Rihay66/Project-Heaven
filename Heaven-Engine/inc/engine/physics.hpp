#pragma once

#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include <iostream>
#include <vector>
#include <math.h>

#include <gameObjs/rigidbodyObject.hpp>
#include <gameObjs/triggerObject.hpp>

//include box2d lib
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>

class b2World;

/* Static Class


*/
class Physics{
    public:
        //List of different trigger objects 
        static std::vector<TriggerObject*> triggerObjs;
        //List of different rigidbody
        static std::vector<PhysicsObject*> rigidbodyObjs;

        //reference to physics world
        static b2World* world;

        //physics iteration values
        static int32_t velocityIterations;
        static int32_t positionIterations;

        //constructors
        Physics() {};

        //Init function that is used after adding all pObjs
        static void init(glm::vec2 gravity = glm::vec2(0.0f, -9.81f));

        /*Check all physics object and update their positions and rotations
        *   NOTE: It's recommended to call this function in a fixed time step, i.e stepUpdate()
        */
        static void updatePhysics();

        //Check all trigger objects
        static void updateTriggers();

        /*Updates physics world which updates physics objects 
        *  NOTE: It's recommended to call this function in a fixed time step, i.e stepUpdate()
        */
        static void updateWorld(float deltaTime);

        //Clear and delete objects, NOTE: deleteting class that inherent either trigger or physics object will cause a memory leak
        static void clearAll();

        //Delete world, NOTE: Make sure to delete trigger and physics objects properly
        static void clearWorld();

        //Clears reference to physics and trigger objects, NOTE: Make sure to delete such references
        static void clearReference();

        //Simple check for aabb collision check
        static bool aabbCollision(GameObject* a, GameObject* b);

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