#include <gameObjs/triggerObject.hpp>

TriggerObject::TriggerObject(glm::vec2 pos, glm::vec2 siz, int sprt, glm::vec4 color) :
GameObject(pos, siz, sprt, color), isDestroyed(false), maxTimeToTrigger(5), trigType(TriggerType::Enter){}

//Define function to check if a object already exists in the passed list
bool isAlreadyPresent(const std::vector<GameObject*>& vec, GameObject* value) {
    return std::find(vec.begin(), vec.end(), value) != vec.end();
}

//Define aabb collision detection
bool aabbCollision(GameObject* a, GameObject* b){
    // collision x-axis?
    bool collisionX = a->position.x + a->size.x >= b->position.x &&
        b->position.x + b->size.x >= a->position.x;
    // collision y-axis?
    bool collisionY = a->position.y + a->size.y >= b->position.y &&
        b->position.y + b->size.y >= a->position.y;
    // collision only if on both axes
    return collisionX && collisionY;
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
        //Check if object is valid to be added to list
        if(obj && obj != nullptr){
            //Check if objects doesn't exist
            if(!isAlreadyPresent(this->lastCollidedObjs, obj)){
                //Add object to list
                this->lastCollidedObjs.push_back(obj);
            }
        }
        break;
    default:
        break;
    }
}

void TriggerObject::exitTriggerObjectCheck(){
    //Check if list is not empty
    if(this->lastCollidedObjs.capacity() <= 0){
        return;
    }

    //Check every object and then call the exit trigger 
    for(GameObject* obj : lastCollidedObjs){
        //Check if one of the objects
        if(!aabbCollision(this, obj)){
            //Call the exit trigger function
            this->onTriggerExit(obj);
            //Then remove object from the list

            //Find object by index
            auto index = std::find(lastCollidedObjs.begin(), lastCollidedObjs.end(), obj);

            //Remove object from list
            if (index != lastCollidedObjs.end()){  // Ensure the object is found
                lastCollidedObjs.erase(index); // Erase
            }
        }
    }
}