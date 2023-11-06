#include <gameObjs/triggerObject.hpp>

TriggerObject::TriggerObject(glm::vec2 pos, glm::vec2 siz, int sprt, glm::vec4 color) :
GameObject(pos, siz, sprt, color), isDestroyed(false), trigType(TriggerType::Enter){
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
        //Take object that collided initially 
        lastObjToCollide = obj;
        break;
    default:
        break;
    }
}