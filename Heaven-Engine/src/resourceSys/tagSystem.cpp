#include <resourceSys/tagSystem.hpp>

//Instantiate static resources
std::vector<TagSystem::objectTag> TagSystem::tagPool;

void TagSystem::addTag(std::string tagName, GameObject* gameObj){
    // add a new object to the pool or make a new one if tag doesn't exist
    
    //Check if list is not empty
    if (tagPool.size() > 0){

        for (int i = 0; i < tagPool.size(); i++){
            // check if object exists in the list
            if (tagPool[i].obj == gameObj){
                // replace it's tag
                tagPool[i].name = tagName;
                return; // stop function
            }
        }
    }

    //*If object doesn't exists then make a new one

    //create a temp data struct storing both tag and object
    objectTag temp;

    temp.name = tagName;
    temp.obj = gameObj;

    //Add to the list
    tagPool.push_back(temp);
}

std::string TagSystem::getTag(GameObject* gameObj){
    //loop to find object and return it's tag
    for(int i = 0; i < tagPool.size(); i++){
        if(tagPool[i].obj == gameObj){
            //return tag name
            return tagPool[i].name;
        }
    }

    return nullptr;
}

//TODO: Refactor to return a list of objects with the same tag
GameObject* TagSystem::getObject(std::string tagName){
    //loop to find object and return it's tag
    for(int i = 0; i < tagPool.size(); i++){
        //check if the name found is the same
        if(tagPool[i].name.compare(tagName) == 0){
            //return object
            return tagPool[i].obj;
        }
    }

    return nullptr;
}

bool TagSystem::checkObject(std::string target, GameObject* gameObj){
    //loop to find tag and then compare if the object is the same as in tag pool
    for(int i = 0; i < tagPool.size(); i++){
        if(tagPool[i].name.compare(target) == 0 && tagPool[i].obj == gameObj){
            //Object was found then return true
            return true;
        }
    }

    //nothing was found then return false by default
    return false;
}

int TagSystem::getAmountOfObjects(){
    //exit function if the list is empty
    if(tagPool.size() <= 0)
        return -1; //stop function from here

    //Return amount objects
    return tagPool.size();
}

void TagSystem::removeObject(GameObject* gameObj){
    //loop to find object to remove from list
    for(int i = 0; i < tagPool.size(); i++){
        if(tagPool[i].obj == gameObj){
            //remove from list
            tagPool.erase(tagPool.begin() + i);
            return; //stop function
        }
    }
}

void TagSystem::removeObjectsWithTag(std::string& tagName){
    //loop to find objects with the passed tag
    for(int i = 0; i < tagPool.size(); i++){
        if(tagPool[i].name.compare(tagName) == 0){
            //remove from list
            tagPool.erase(tagPool.begin() + i);
        }
    }
}

void TagSystem::clear(){
    //Remove references to pointers
    tagPool.clear();
}