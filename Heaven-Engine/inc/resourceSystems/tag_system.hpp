#pragma once

#ifndef TAG_SYSTEM_HPP
#define TAG_SYSTEM_HPP

// include standard libraries
#include <string>
#include <vector>

// include gameobject class
#include <gameObjects/game_object.hpp>

/* A Static singleton TagSystem class that hosts several
 functions to add, edit, find GameObjects that have a set tag 
 to a static tag pool. All functions and tag pool are static.
 This Class has no public constructor defined.
*/
class TagSystem{
    public:
        //*Adder Funcs

        // add a tag and object to the resource pool, if object already exists then replace it's tag
        static void addTag(std::string tagName, GameObject* gameObj);

        //*Helper Funcs
        
        // get object from the list and replace the tag of in the tag pool, not the object's tag itself
        static void replaceTag(std::string tagName, GameObject* gameObj);

        //*Getter Funcs

        // get a tag from a object in the tag pool
        static std::string getTag(GameObject* gameObj);
        // get objects from the tag pool by tag
        static std::vector<GameObject*> getObject(std::string tagName);
        // check if tag pertains to a passed object that exists in tag pool
        static bool checkObject(std::string target, GameObject* gameObj);
        // get amount of objects in the tag system
        static int getAmountOfObjects();

        //*Remover Funcs

        // get object and remove from list
        static void removeObject(GameObject* gameObj);

        // get and remove objects with a certain tag
        static void removeObjectsWithTag(std::string& tagName);

        // remove references and clear tag pool
        static void clear();


    private:
        // define data type that contains both tag and gameobject
        struct objectTag{
            std::string name;
            GameObject* obj;
        };
        // static resource. Contains GameObjects alongside with their assigned tag
        static std::vector<objectTag> tagPool;
        // private constructor
        TagSystem(){}
};

#endif