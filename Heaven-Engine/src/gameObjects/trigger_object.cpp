#include <gameObjects/trigger_object.hpp>

TriggerObject::TriggerObject(int sprt, glm::vec2 pos, glm::vec2 siz, glm::vec4 color) :
GameObject(sprt, pos, siz, color), maxTimeToTrigger(5), trigType(TriggerType::Enter){}

TriggerObject::~TriggerObject(){
    this->collidedObjs.clear();
}

// define function to check if a object already exists in the passed list
bool TriggerObject::isAlreadyPresent(const std::vector<GameObject*>& vec, GameObject* value) {
    return std::find(vec.begin(), vec.end(), value) != vec.end();
}

// define aabb collision detection
bool TriggerObject::aabbCollision(GameObject* b){
    // Calculate the sides of the rectangles with the offset considered

    // Check for no overlap
    bool collisionX = (this->position.x + this->size.x / 2.0f) >= (b->position.x - b->size.x / 2.0f) && (this->position.x - this->size.x / 2.0f) <= (b->position.x + b->size.x / 2.0f);
    bool collisionY = (this->position.y + this->size.y / 2.0f) >= (b->position.y - b->size.y / 2.0f) && (this->position.y - this->size.y / 2.0f) <= (b->position.y + b->size.y / 2.0f);

    // If the rectangles overlap on both axes, a collision is detected
    return collisionX && collisionY;
}

TriggerType TriggerObject::getTriggerType(){
    return this->trigType;
}

void TriggerObject::setTimeToTrigger(int amount){
    if(amount < 1){
        this->maxTimeToTrigger = 1;
    }

    this->maxTimeToTrigger = amount;
}

void TriggerObject::triggerCollisionCallback(GameObject* obj){

    switch (this->trigType){
        case TriggerType::Enter:
            // call enter trigger 
            onTriggerEnter(obj);
            break;
        case TriggerType::Stay:
            // wait till a value reaches dersired max time
            if(currentTimeToTrigger >= maxTimeToTrigger){
                // call trigger stay
                onTriggerStay(obj);
                // reset current timer
                currentTimeToTrigger = 0;
            }else
                currentTimeToTrigger++; // increment time
            break;
        case TriggerType::Exit:
            // check if object is valid to be added to list
            if(obj && obj != nullptr){
                // check if objects doesn't exist
                if(!isAlreadyPresent(this->collidedObjs, obj)){
                    // add object to list
                    this->collidedObjs.push_back(obj);
                }
            }
            break;
        default:
            break;
    }
}

void TriggerObject::exitTriggerObjectCheck(){
    // check if list is not empty
    if(this->collidedObjs.capacity() <= 0){
        return;
    }

    // check every object and then call the exit trigger 
    for(GameObject* obj : collidedObjs){
        // check if one of the objects
        if(!aabbCollision(obj)){
            // call the exit trigger function
            this->onTriggerExit(obj);
            // then remove object from the list

            // find object by index
            auto index = std::find(collidedObjs.begin(), collidedObjs.end(), obj);

            // remove object from list
            if (index != collidedObjs.end()){  // ensure the object is found
                collidedObjs.erase(index); // erase
            }
        }
    }
}