#include "../inc/physics.hpp"

//TODO: Implement Box 2D

Physics::Physics(){
}

Physics::~Physics(){
    //delete any pointer 
    pObjs.clear();
    rigidbodyObjs.clear();
    triggerObjs.clear();

    world = nullptr;
    delete world;
}

void Physics::init(glm::vec2 gravity){
    //Set up box 2d world
    world = new b2World({0.0f, 0.0f});

    //Check if there is an empty list of rigidbodies
    if(pObjs.size() <= 0){
        std::cout << "ERROR: list of physics objects is ZERO!!!" << "\n";
        return;
    }

    //organize objects by flags sucha as non triggers and triggers
    for(physicsObject* obj : pObjs){
        if(obj->isTrigger)
            triggerObjs.push_back(obj);
        else
            rigidbodyObjs.push_back(obj);
    }

    //Loop through list of rigidbodies and add them to the box2d world
    for(physicsObject* obj : rigidbodyObjs){

        //set up rigidbody and boxcollider
        b2BodyDef bodyDef;
        bodyDef.type = RbToB2Types(obj->rb.Type);
        bodyDef.position.Set(obj->position.x, obj->position.y);
        bodyDef.angle = obj->rotation;

        //create body
        b2Body* body = world->CreateBody(&bodyDef);
        body->SetFixedRotation(obj->rb.fixedRotation);
        obj->rb.runtimeBody = body;

        //set up box collider
    }

}

//TODO: When a physics object is destroyed remove from list
void Physics::CheckCollisions(physicsObject &plr){

    //Check rigidbodies
    for(physicsObject* obj : rigidbodyObjs){
        
    }

    //Check for triggers
    for(physicsObject* obj : triggerObjs){
        //Check every physics object with the player
        if(!obj->isDestroyed){
            if(aabbCollision(plr, *obj)){
                //Execture any code from the trigger
                obj->triggerCollision();
            }
        }
    }
}

bool Physics::aabbCollision(physicsObject &a, physicsObject &b){
    // collision x-axis?
    bool collisionX = a.position.x + a.size.x >= b.position.x &&
        b.position.x + b.size.x >= a.position.x;
    // collision y-axis?
    bool collisionY = a.position.y + a.size.y >= b.position.y &&
        b.position.y + b.size.y >= a.position.y;
    // collision only if on both axes
    return collisionX && collisionY;
}