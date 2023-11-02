#include <resourceSys/tagSystem.hpp>

//Instantiate static resources
std::map<std::string, GameObject&> TagSystem::objectsWithTag;

void TagSystem::addTag(std::string& tagName, GameObject& gameObj){
    //Check if object already exists in the pool first
    if(objectsWithTag[tagName] == gameObj){

    }else{ //Object doesn't exist in the pool then add object and the ag

    }
    
    //add object to the pool 

}

std::string getTag(GameObject& gameObj){

}

GameObject getObjects(std::string tagName){

}