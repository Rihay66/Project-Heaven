#include <resourceSys/tagSystem.hpp>

// instantiate static resources
std::vector<TagSystem::objectTag> TagSystem::tagPool;

void TagSystem::addTag(std::string tagName, GameObject* gameObj){
    // add a new object to the pool with the tag
    
    //!Check if object and tag already exist in the tagPool
    //check if list is not empty
    if (tagPool.size() > 0){
        for (int i = 0; i < tagPool.size(); i++){
            // check if object exists in the list
            if (tagPool[i].obj == gameObj && tagPool[i].name.compare(tagName) == 0){
                return; // stop function and avoid making a new object being the tag pool
            }
        }
    }

    //*If object doesn't exists then make a new one

    // create a temp data struct storing both tag and object
    objectTag temp;

    // set the game objects tag to be the tag assigned
    if(gameObj && gameObj != nullptr){
        gameObj->setTag(tagName);
    }else{
        // stop function as game object doesn't exist
        return;
    }
    
    temp.name = tagName;
    temp.obj = gameObj;

    // add to the list
    tagPool.push_back(temp);

    //TODO: Organize list by using the tag string from descending to ascending order
}

void TagSystem::replaceTag(std::string target, GameObject* gameObj){
    // loop to find object and replace it's tag
    for(int i = 0; i < tagPool.size(); i++){
        if(tagPool[i].obj == gameObj){
            // replace tag on tag pool and the object itself
            tagPool[i].name = target;

            //stop function 
            return;
        }
    }
}

std::string TagSystem::getTag(GameObject* gameObj){
    // loop to find object and return it's tag
    for(int i = 0; i < tagPool.size(); i++){
        if(tagPool[i].obj == gameObj){
            // return tag name
            return tagPool[i].name;
        }
    }

    // couldn't find the object in the tag pool
    return nullptr;
}

std::vector<GameObject*> TagSystem::getObject(std::string target){
    // create temporary pool that will contain objects with similar given target tag
    std::vector<GameObject*> pool;

    // linear looop to find tag and add to pool of objects similar tag
    for(int i = 0; i < tagPool.size(); i++){
        if(tagPool[i].name.compare(target) == 0){
            // add object with target tag
            pool.push_back(tagPool[i].obj);
        }
    }

    // return either an empty pool or populated one
    return pool;
}

//TODO: Refactor to use binary search for the target
bool TagSystem::checkObject(std::string target, GameObject* gameObj){
    // linear loop to find tag and then compare if the object is the same as in tag pool
    for(int i = 0; i < tagPool.size(); i++){
        if(tagPool[i].name.compare(target) == 0 && tagPool[i].obj == gameObj){
            // object was found then return true
            return true;
        }
    }

    // nothing was found then return false by default
    return false;
}

int TagSystem::getAmountOfObjects(){
    // exit function if the list is empty
    if(tagPool.size() <= 0)
        return -1; // stop function from here

    // return amount objects
    return tagPool.size();
}

void TagSystem::removeObject(GameObject* gameObj){
    // loop to find object to remove from list
    for(int i = 0; i < tagPool.size(); i++){
        if(tagPool[i].obj == gameObj){
            // remove from list
            tagPool.erase(tagPool.begin() + i);
            return; // stop function
        }
    }
}

void TagSystem::removeObjectsWithTag(std::string& tagName){
    // loop to find objects with the passed tag
    for(int i = 0; i < tagPool.size(); i++){
        if(tagPool[i].name.compare(tagName) == 0){
            // remove from list
            tagPool.erase(tagPool.begin() + i);
        }
    }
}

void TagSystem::clear(){
    // remove references to pointers
    tagPool.clear();
}