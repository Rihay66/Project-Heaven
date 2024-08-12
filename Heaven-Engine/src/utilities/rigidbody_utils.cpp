#include <utilities/rigidbody_utils.hpp>

// include Box2D
#include <box2d/b2_body.h>

void ApplyForce(glm::vec2 force, void* body){
    // cast the given body to b2Body
    b2Body* b = static_cast<b2Body*>(body);

    // check if b is not null
    if(b != nullptr){
        //  apply force
        b->ApplyForce({force.x, force.y}, b->GetWorldCenter(), true);
    }
}

void ApplyLinearVelocity(glm::vec2 velocity, void* body){
    // cast the given body to b2Body
    b2Body* b = static_cast<b2Body*>(body);

    // check if b is not null
    if(b != nullptr){
        // grab the velocity of the body
        b2Vec2 vel = b->GetLinearVelocity();

        //* Apply the velocity on all axis

        vel.x += velocity.x;
        vel.y += velocity.y;

        // set the new velocity to the body
        b->SetLinearVelocity(vel);
    }
}

void SetLinearVelocity(glm::vec2 velocity, void *body){
    // cast the given body to b2Body
    b2Body* b = static_cast<b2Body*>(body);

    // check if b is not null
    if(b != nullptr){
        // grab the velocity of the body
        b2Vec2 vel = b->GetLinearVelocity();

        //* Set the velocity on all axis

        vel.x = velocity.x;
        vel.y = velocity.y;

        // set the new velocity to the body
        b->SetLinearVelocity(vel);
    }
}

void SetYLinearVelocity(float y, void *body){
    // cast the given body to b2Body
    b2Body* b = static_cast<b2Body*>(body);

    // check if b is not null
    if(b != nullptr){
        // grab the velocity of the body
        b2Vec2 vel = b->GetLinearVelocity();

        //* Set the velocity on Y axis

        vel.y = y;

        // set the new velocity to the body
        b->SetLinearVelocity(vel);
    }
}

void SetXLinearVelocity(float x, void *body){
    // cast the given body to b2Body
    b2Body* b = static_cast<b2Body*>(body);

    // check if b is not null
    if(b != nullptr){
        // grab the velocity of the body
        b2Vec2 vel = b->GetLinearVelocity();

        //* Set the velocity on X axis

        vel.x = x;

        // set the new velocity to the body
        b->SetLinearVelocity(vel);
    }
}