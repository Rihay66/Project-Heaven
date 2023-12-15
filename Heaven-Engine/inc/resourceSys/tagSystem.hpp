#pragma once

#ifndef TAGSYSTEM_HPP
#define TAGSYSTEM_HPP

//Include standard libraries
#include <string>
#include <vector>

//include gameobject class
#include <gameObjs/gameObject.hpp>

/* Static singleton  TagSystem class 


*/

class TagSystem{
public:
    //*Adder Funcs

    // add a tag and object to the resource pool, if object already exists then replace it's tag
    static void addTag(std::string tagName, GameObject* gameObj);
    //*Getter Funcs

    // get a tag from a object in the tag pool
    static std::string getTag(GameObject* gameObj);
    // get object from the tag pool by tag
    static GameObject* getObject(std::string tagName);
    // check if tag pertains to a passed object that exists in tag pool
    static bool checkObject(std::string target, GameObject* gameObj);
    // get amount of objects in the tag system
    static int getAmountOfObjects();

    //*Remover Funcs

    // get object and remove from list
    static void removeObject(GameObject* gameObj);

    // get and remove objects with a certain tag
    static void removeObjectsWithTag(std::string& tagName);

private:
    //define data type that contains both tag and gameobject
    struct objectTag{
        std::string name;
        GameObject* obj;
    };
    // resource storage 
    static std::vector<objectTag> objectsWithTag;
    // private constructor
    TagSystem(){}
};

#endif