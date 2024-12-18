#pragma once

#ifndef PHYSICS_HPP
#define PHYSICS_HPP

#include <vector>

//? Temporary inclusion of components
#include <ecs/components/transform.hpp>
#include <ecs/components/rigidbody.hpp>
#include <ecs/components/boxcollider.hpp>

// include interpolation
#include "engine/components/interpolation.hpp"

// include GLM
#include <glm/glm.hpp>

// include box2d library
#include <box2d/box2d.h>

// redeclare the box2d b2World class for engine use
class b2World;

//TODO: Remove the use of raw pointers when keeping a reference to a component

// define a Physics 'Object'
struct PhysicsObject {
  Transform2D* transform;
  BoxCollider2D* collider;
  Rigidbody2D* rb;
  Interpolation* inter = nullptr;
};

/* Static Singleton Physics class that hosts functions to add
 either PhysicsObject into the physics engine.
 Objects can be added at any time after init(). Use update 
 functions to update PhysicsObjects. All functions and 
 resources are static and no public constructor is defined.  
 (NOTE: update functions don't work until init() has been called once)
*/
class Physics {
    public:
        //* Initializer functions

        /* initializer function to initialize the physics world and physicsObject
        * NOTE: Must be called once. Displays a warning that init() was called again!
        */
        static void Init(glm::vec2 gravity = glm::vec2(0.0f, -9.81f));

        //* Adder functions

        // create a Physics Object to the physics engine, returns reference of the Physics Object 
        static PhysicsObject CreatePhysicsObject(Transform2D& transform, BoxCollider2D& collider, Rigidbody2D& rigidbody);

        // create a Physics Object to the physics engine, returns reference of the Physics Object 
        static PhysicsObject CreatePhysicsObject(Transform2D& transform, BoxCollider2D& collider, Rigidbody2D& rigidbody, Interpolation& interpolation);

        // register components that makes up a Physics Object to the physics engine, no Physics Object is created
        static void RegisterPhysicsObject(Transform2D& transform, BoxCollider2D& collider, Rigidbody2D& rigidbody);

        // register components that makes up a Physics Object to the physics engine, no Physics Object is created
        static void RegisterPhysicsObject(Transform2D& transform, BoxCollider2D& collider, Rigidbody2D& rigidbody, Interpolation& interpolation);

        //* Setter functions

        /* set the physics substep iteration, by default value is 4
        * NOTE: Passed value cannot be less than 1
        */
        static void SetPhysicsSubStepIterations(int32_t iter);

        //* Update functions

        /* check all physics object and update their positions and rotations
        *   NOTE: It's recommended to call this function in a fixed time step, i.e stepUpdate()
        */
        static void UpdatePhysics();

        /* check given components and update given transform and rigidbody components
        *   NOTE: It's recommended to call this function in a fixed time step, i.e stepUpdate()
        */
        static void UpdateRegisteredObject(Transform2D& transform, Rigidbody2D& rigidbody);

        /* check given components and update given transform and rigidbody components
        *   NOTE: It's recommended to call this function in a fixed time step, i.e stepUpdate()
        */
        static void UpdateRegisteredObject(Transform2D& transform, Rigidbody2D& rigidbody, Interpolation& inter);

        /* updates physics world which updates physics objects 
        *  NOTE: It's recommended to call this function in a fixed time step, i.e stepUpdate()
        */
        static void UpdateWorld(float deltaTime);

        //* Helper functions

        //TODO: Make a function that destroys a specified body

        //TODO: Make a OBB function to allow detecting rotational collisions

        // simple check for aabb collision check
        static bool AABBCollision(Transform2D& a, Transform2D& b);

        // enum translate between box2d and rigidbodyObject class
        static b2BodyType RbToB2Types(BodyType bodyType);

    private:
        // private reference storage of all Physics Objects
        static std::vector<PhysicsObject> physicsObjs;

        //* physics iteration values

        static int32_t substepIterations;

        // reference to physics world
        static b2WorldId world;

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