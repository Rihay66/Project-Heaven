#pragma once

#ifndef TAGSYSTEM_HPP
#define TAGSYSTEM_HPP

//Include standard libraries
#include <string>
#include <map>

//include gameobject class
#include <gameObjs/gameObject.hpp>

/* Static singleton  TagSystem class 


*/

class TagSystem{
public:
    //*Adder Funcs

    // add a tag and object to the resource pool, if object already exists then replace it's tag
    static void addTag(std::string& tagName, GameObject& gameObj);
    //*Getter Funcs

    // get a tag from a object in the tag pool
    static std::string getTag(GameObject& gameObj);
    // get object from the tag pool by tag
    static GameObject getObject(std::string tagName);

private:
    // resource storage
    //? This may change to a vector list, for better performance 
    static std::map<std::string, GameObject&> objectsWithTag;
    // private constructor
    TagSystem(){}
};

#endif