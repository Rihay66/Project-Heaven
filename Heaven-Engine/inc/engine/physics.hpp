#pragma once

#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include <vector>

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
 Objects can be added at any time after init(). Use update 
 functions to update TriggerObjects and PhysicsObjects.
 (NOTE: update functions don't work until init() has been called once)
*/
class Physics{
    public:
        //* Initializer functions

        /* initializer function to initialize the physics world and physicsObject
        * NOTE: Must be called once. Displays a warning that init() was called again!
        */
        static void Init(glm::vec2 gravity = glm::vec2(0.0f, -9.81f));

        //* Adder functions

        // add trigger object to the physics engine
        static TriggerObject* AddTriggerObject(TriggerObject* obj);

        // add physics object to the physics engine
        static PhysicsObject* AddPhysicsObject(PhysicsObject* obj);

        //* Setter functions

        /* set the physics velocity iteration, by default value is 8
        * NOTE: Passed value cannot be less than 1
        */
        static void SetPhysicsVelocityIterations(int32_t iter);

        /* set the physics position iteration, by default value is 4
        * NOTE: Passed value cannot be less than 1
        */
        static void SetPhysicsPositionIterations(int32_t iter);

        //* Update functions

        /* check all physics object and update their positions and rotations
        *   NOTE: It's recommended to call this function in a fixed time step, i.e stepUpdate()
        */
        static void UpdatePhysics();

        // check all trigger objects
        static void UpdateTriggers();

        /* updates physics world which updates physics objects 
        *  NOTE: It's recommended to call this function in a fixed time step, i.e stepUpdate()
        */
        static void UpdateWorld(float deltaTime);

        //* Helper functions

        // simple check for aabb collision check
        static bool AABBCollision(GameObject* a, GameObject* b);

        // enum translate between box2d and rigidbodyObject class
        static b2BodyType RbToB2Types(BodyType bodyType);
    private:
        // private reference storage

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

        //* Clear function
        
        // dereference all reference to objects and delete the physics world
        static void Clear();

        //! Currently EXPERIMENTAL, may cause exceptions or segfaults
        // private boolean to track automatic clear()
        static bool isAutoClearSet;
        // set up automatic de-allocation of loaded resources
        static void SetUpAutoClear();
};

#endif