#include <gameObjs/triggerObject.hpp>

TriggerObject::TriggerObject(glm::vec2 pos, glm::vec2 siz, int sprt, glm::vec4 color) :
GameObject(pos, siz, sprt, color), isDestroyed(false), maxTimeToTrigger(5), trigType(TriggerType::Enter){}

TriggerObject::~TriggerObject(){
    this->collidedObjs.clear();
}

//Define function to check if a object already exists in the passed list
bool TriggerObject::isAlreadyPresent(const std::vector<GameObject*>& vec, GameObject* value) {
    return std::find(vec.begin(), vec.end(), value) != vec.end();
}

//Define aabb collision detection
bool aabbCollision(GameObject* a, GameObject* b){
    // Calculate the sides of the rectangles with the offset considered

    // Check for no overlap
    bool collisionX = (a->position.x + a->size.x / 2.0f) >= (b->position.x - b->size.x / 2.0f) && (a->position.x - a->size.x / 2.0f) <= (b->position.x + b->size.x / 2.0f);
    bool collisionY = (a->position.y + a->size.y / 2.0f) >= (b->position.y - b->size.y / 2.0f) && (a->position.y - a->size.y / 2.0f) <= (b->position.y + b->size.y / 2.0f);

    // If the rectangles overlap on both axes, a collision is detected
    return collisionX && collisionY;
}

void TriggerObject::triggerCollisionCallback(GameObject* obj){

    switch (this->trigType){
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
                if(!isAlreadyPresent(this->collidedObjs, obj)){
                    //Add object to list
                    this->collidedObjs.push_back(obj);
                }
            }
            break;
        default:
            break;
    }
}

void TriggerObject::exitTriggerObjectCheck(){
    //Check if list is not empty
    if(this->collidedObjs.capacity() <= 0){
        return;
    }

    //Check every object and then call the exit trigger 
    for(GameObject* obj : collidedObjs){
        //Check if one of the objects
        if(!aabbCollision(this, obj)){
            //Call the exit trigger function
            this->onTriggerExit(obj);
            //Then remove object from the list

            //Find object by index
            auto index = std::find(collidedObjs.begin(), collidedObjs.end(), obj);

            //Remove object from list
            if (index != collidedObjs.end()){  // Ensure the object is found
                collidedObjs.erase(index); // Erase
            }
        }
    }
}