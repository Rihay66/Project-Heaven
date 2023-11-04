#include <resourceSys/tagSystem.hpp>

//Instantiate static resources
std::vector<TagSystem::objectTag> TagSystem::objectsWithTag;

void TagSystem::addTag(std::string tagName, GameObject* gameObj){
    // add a new object to the pool or make a new one if tag doesn't exist
    
    //Check if list is not empty
    if (objectsWithTag.size() > 0){

        for (int i = 0; i < objectsWithTag.size(); i++){
            // check if object exists in the list
            if (objectsWithTag[i].obj == gameObj){
                // replace it's tag
                objectsWithTag[i].name = tagName;
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
    objectsWithTag.push_back(temp);
}

std::string TagSystem::getTag(GameObject* gameObj){
    //loop to find object and return it's tag
    for(int i = 0; i < objectsWithTag.size(); i++){
        if(objectsWithTag[i].obj == gameObj){
            //return tag name
            return objectsWithTag[i].name;
        }
    }

    return nullptr;
}

GameObject* TagSystem::getObject(std::string tagName){
    //loop to find object and return it's tag
    for(int i = 0; i < objectsWithTag.size(); i++){
        //check if the name found is the same
        if(objectsWithTag[i].name.compare(tagName) == 0){
            //return object
            return objectsWithTag[i].obj;
        }
    }

    return nullptr;
}

int TagSystem::getAmountOfObjects(){
    //exit function if the list is empty
    if(objectsWithTag.size() <= 0)
        return -1; //stop function from here

    //Return amount objects
    return objectsWithTag.size();
}

void TagSystem::removeObject(GameObject* gameObj){
    //loop to find object to remove from list
    for(int i = 0; i < objectsWithTag.size(); i++){
        if(objectsWithTag[i].obj == gameObj){
            //remove from list
            objectsWithTag.erase(objectsWithTag.begin() + i);
            return; //stop function
        }
    }
}

void TagSystem::removeObjectsWithTag(std::string& tagName){
    //loop to find objects with the passed tag
    for(int i = 0; i < objectsWithTag.size(); i++){
        if(objectsWithTag[i].name.compare(tagName) == 0){
            //remove from list
            objectsWithTag.erase(objectsWithTag.begin() + i);
        }
    }
}