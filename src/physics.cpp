#include "../inc/physics.hpp"

//TODO: Implement Box 2D

Physics::Physics(){
}

Physics::~Physics(){
    //delete any pointer 
    pObjs.clear();
    rigidbodyObjs.clear();
    triggerObjs.clear();
}

void Physics::init(glm::vec2 gravity){
    //Set up box 2d world

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