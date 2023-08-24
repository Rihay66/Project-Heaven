#include "../inc/physics.hpp"

Physics::Physics(){}

Physics::~Physics(){
    //delete any pointer 
    pObjs.clear();
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
                //Get magnitude 
                OverlapInfo overlap = calcCollisionMagnitude(plr, *obj);

                //Determine the player direction
                //Check if the magnitude is positive or negative then properly offset the player
                    
                //Make a visualizer to show the offset
                plr.position.y += overlap.yOverlap;
                //plr.position.x += overlap.xOverlap;
                    
                //debug
                std::cout << "Y direction offset: " << overlap.yOverlap << std::endl;
                

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
    bool collisionY = a.position.y + a.size.y >= b.position.y &&
        b.position.y + b.size.y >= a.position.y;
    // collision only if on both axes
    return collisionX && collisionY;
}

Physics::OverlapInfo Physics::calcCollisionMagnitude(physicsObject &a, physicsObject &b){
    OverlapInfo overlap;

    //Get X axis magnitude
    float x = (((a.position.x + a.size.x) - (b.position.x + b.size.x)) / (a.size.x + b.size.x)) / ((b.size.x * 2.0f) + a.size.x * 2.0f);
    //Get Y axis magnitude
    float y = (((a.position.y + a.size.y) - (b.position.y + b.size.y)) / (a.size.y + b.size.y)) / ((b.size.y * 2.0f) + a.size.y * 2.0f);

    //store magnitudes into overlap struct
    overlap.xOverlap = x;
    overlap.yOverlap = y;

    return overlap;
}
/*
float Physics::calcCollisionXMagnitude(physicsObject &a, physicsObject &b){
    //What this func should do is 
    //Calculate the magnitude on the X axis
    float x = (a.position.x + a.size.x) - (b.position.x + b.size.x);

    return x;
}

float Physics::calcCollisionYMagnitude(physicsObject &a, physicsObject &b){
    //What this func should do is 
    //Calculate the magnitude on the Y axis
    float y = (a.position.y + a.size.y) - (b.position.y + b.size.y);

    return y;
}
*/