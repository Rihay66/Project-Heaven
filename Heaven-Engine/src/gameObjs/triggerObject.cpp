#include <gameObjs/triggerObject.hpp>
#include <stdio.h>

TriggerObject::TriggerObject(glm::vec2 pos, glm::vec2 siz, int sprt, glm::vec4 color) :
GameObject(pos, siz, sprt, color), isDestroyed(false), maxTimeToTrigger(5), trigType(TriggerType::Enter),
lastObjToCollide(nullptr){
}

void TriggerObject::triggerCollisionCallback(GameObject* obj){
    switch (this->trigType)
    {
    case TriggerType::Enter:
        //Call enter trigger 
        onTriggerEnter(obj);
        break;
    case TriggerType::Stay:
        //Wait till a value reaches dersired max time
        if(currentTimeToTrigger >= maxTimeToTrigger){
            //Call trigger stay
            onTriggerStay(obj);
            //reset current timer
            currentTimeToTrigger = 0;
        }else
            currentTimeToTrigger++; //increment time
        break;
    case TriggerType::Exit:
        if(!targetTag.empty()){
            //check if object is target
            if(TagSystem::checkObject(targetTag, obj)){
                //Take object that collided initially 
                lastObjToCollide = obj;
            }
        }else{
            //Display error
            printf("ERROR: trigger object doesn't have a set 'target Tag'!\n");
        }
        break;
    default:
        break;
    }
}