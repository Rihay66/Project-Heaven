#pragma once

#ifndef RIGIDBODYOBJECT_HPP
#define RIGIDBODYOBJECT_HPP

#include <gameObjs/gameObject.hpp>
#include <resourceSys/componentUtils.hpp>
#include <box2d/b2_body.h>

/* Deriving Class from GameObject. This object allows for
 physics to take hold by including this object into the Physics class.
 Overwritting the physicBody() allows for manipulation of the rigidbody
 and adding additional functionality of the object.
*/
class PhysicsObject : public GameObject{
    private: 
        // used as a "destroyed" flag for internal use
        bool isDestroyed;

    public:
        //Declare Rigidbody
        Rigidbody rb;
        //declare BoxCollider
        BoxCollider collider;

        // constructor(s)
        PhysicsObject(int sprt, glm::vec2 pos = glm::vec2(0.0f), glm::vec2 siz = glm::vec2(1.0f), glm::vec4 color = glm::vec4(1.0f), bool interpolation = true, bool destroyed = false);

        /* used to define to make changes to the b2 body and returns a modified b2Body*
        * Usage: cast out a b2Body* from the rigidbody.runtimeBody and modify it using
        * Box2D methods and then return the modified b2Body* to allow to modifications
        * to take place in the physics engine.
        */
        virtual b2Body* physicBody(){return (b2Body*)rb.runtimeBody;}

        /* sets this object to have a "destroyed" flag
        * NOTE: The physics engine will skip updating this object if destroyed
        */
        void Destroy();

        //* Getter functions

        // returns the "destroyed" flag of this object
        bool getDestroyedStatus();
};

#endif