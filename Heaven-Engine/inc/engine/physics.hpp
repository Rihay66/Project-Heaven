#pragma once

#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include <vector>
#include <math.h>

#include <gameObjects/physics_object.hpp>
#include <gameObjects/trigger_object.hpp>

// include box2d library
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_polygon_shape.h>

// redeclare the box2d b2World class for engine use
class b2World;

/* Static Singleton Physics class that hosts functions to add
 either TriggerObject or PhysicsObject into the physics engine.
 Objects can be added at any time after init() (not recommended).
 Use update functions to update TriggerObjects and PhysicsObjects.
 (NOTE: update functions don't work until init() has been called once)
*/
class Physics{
    public:
        //* Initializer functions

        /* initializer function to initialize the physics world and physicsObject
        * NOTE: Must be called once! If intentionally calling init again make sure to clearWorld() before calling init() again
        */
        static void init(glm::vec2 gravity = glm::vec2(0.0f, -9.81f));

        //* Adder functions

        // add trigger object to the physics engine
        static TriggerObject* addTriggerObject(TriggerObject* obj);

        // add physics object to the physics engine
        static PhysicsObject* addPhysicsObject(PhysicsObject* obj);

        //* Setter functions

        /* set the physics velocity iteration, by default value is 8
        * NOTE: Passed value cannot be less than 1
        */
        static void setPhysicsVelocityIterations(int32_t iter);

        /* set the physics position iteration, by default value is 4
        * NOTE: Passed value cannot be less than 1
        */
        static void setPhysicsPositionIterations(int32_t iter);

        //* Update functions

        /* check all physics object and update their positions and rotations
        *   NOTE: It's recommended to call this function in a fixed time step, i.e stepUpdate()
        */
        static void updatePhysics();

        // check all trigger objects
        static void updateTriggers();

        /* updates physics world which updates physics objects 
        *  NOTE: It's recommended to call this function in a fixed time step, i.e stepUpdate()
        */
        static void updateWorld(float deltaTime);

        //* Cleaner functions

        /* clear and delete objects
        * NOTE: Deleteting a class that inherent either trigger or physics object will cause a memory leak
        */
        static void clearAll();

        /* delete world
        * NOTE: Make sure to delete trigger and physics objects properly
        */
        static void clearWorld();

        /* clears reference to physics and trigger objects 
        * NOTE: Make sure to delete such references
        */
        static void clearReference();

        //* Helper functions

        // simple check for aabb collision check
        static bool aabbCollision(GameObject* a, GameObject* b);

        // enum translate between box2d and rigidbodyObject class
        static b2BodyType RbToB2Types(BodyType bodyType);
    private:
        // list of different trigger objects 
        static std::vector<TriggerObject*> triggerObjs;
        // list of different rigidbody
        static std::vector<PhysicsObject*> rigidbodyObjs;

        //* physics iteration values

        static int32_t velocityIterations;
        static int32_t positionIterations;

        // reference to physics world
        static b2World* world;

        // overwrittable State struct
        static State mState;

        // private constructor
        Physics() {};
};

#endif