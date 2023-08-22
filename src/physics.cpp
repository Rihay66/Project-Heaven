#include "../inc/physics.hpp"

Physics::Physics(){}

Physics::~Physics(){
    //delete any pointer 
    pObjs.clear();
}

static float calcCollisionMagnitude(physicsObject &a, physicsObject &b){
    //What this func should do is 
    //Calculate the magnitude on the X axis
    float x = (a.position.x + a.size.x) - (b.position.x + b.size.x);
    float y = (a.position.y + a.size.y) - (b.position.y + b.size.y);

    float amount = x + y;
    return amount;
}

void Physics::CheckCollisions(physicsObject &plr){
    //Check if the size of the objects is empty then stop function
    if(pObjs.size() <= 0)
        return;

    for(physicsObject* obj : pObjs){
        //Check every physics object with the player
        if(!obj->isDestroyed){
            if(aabbCollision(plr, *obj)){
                //TODO: offset the player, depending on how much the intersection was by the size and position
                //Apply magnitude
                std::cout << "Total magnitude: " << calcCollisionMagnitude(plr, *obj) << "| X Magnitude: " << calcCollisionXMagnitude(plr, *obj) << "| Y Magnitude" << calcCollisionYMagnitude(plr, *obj) << std::endl;
                //plr.position.x += calcCollisionXMagnitude(plr, *obj);
                //plr.position.y += calcCollisionYMagnitude(plr, *obj) / 3;
            }
        }

        //TODO: When a physics object is destroyed remove from list
    }
}

bool Physics::aabbCollision(physicsObject &a, physicsObject &b){
    // collision x-axis?
    bool collisionX = a.position.x + a.size.x >= b.position.x &&
        b.position.x + b.size.x >= a.position.x;
    // collision y-axis?
    bool collisionY = a.position.y + a.size.y >= a.position.y &&
        b.position.y + b.size.y >= a.position.y;
    // collision only if on both axes
    return collisionX && collisionY;
}

float Physics::calcCollisionXMagnitude(physicsObject &a, physicsObject &b){
    //What this func should do is 
    //Calculate the magnitude on the X axis
    float x = ((a.position.x + a.size.x) - b.position.x) - ((b.position.x + b.size.x) - a.position.x);

    return x;
}

float Physics::calcCollisionYMagnitude(physicsObject &a, physicsObject &b){
    //What this func should do is 
    //Calculate the magnitude on the Y axis
    float y = (a.position.y + a.size.y) - (b.position.y + b.size.y);

    return y;
}
