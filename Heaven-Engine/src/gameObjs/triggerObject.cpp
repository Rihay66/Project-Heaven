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
        //Call stay trigger
        onTriggerStay(obj);
        break;
    case TriggerType::Exit:
        //Call exit trigger
        onTriggerExit(obj);
        break;
    default:
        break;
    }
}