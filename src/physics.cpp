#include "../inc/physics.hpp"

physics::physics(){}

physics::~physics(){
    //delete any pointer 
    pObjs.clear();
}

void physics::CheckCollisions(physicsObject &plr){
    //Check if the size of the objects is empty then stop function
    if(pObjs.size() <= 0)
        return;

    for(physicsObject* obj : pObjs){
        //Check every physics object with the player
        if(!obj->isDestroyed){
            if(aabbCollision(plr, *obj)){
                //TODO: offset the player, depending on how much the intersection was by the size and position
                
            }
        }

        //TODO: When a physics object is destroyed remove from list
    }
}

bool physics::aabbCollision(physicsObject &a, physicsObject &b){
    // collision x-axis?
    bool collisionX = a.position.x + a.size.x >= b.position.x &&
        b.position.x + b.size.x >= a.position.x;
    // collision y-axis?
    bool collisionY = a.position.y + a.size.y >= a.position.y &&
        b.position.y + b.size.y >= a.position.y;
    // collision only if on both axes
    return collisionX && collisionY;
}