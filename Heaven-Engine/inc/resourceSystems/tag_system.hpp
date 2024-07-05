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
        //* adder Funcs

        // add a tag and object to the resource pool, if object already exists then replace it's tag
        static void AddTag(std::string tagName, GameObject* gameObj);

        //* helper Funcs
        
        // get object from the list and replace the tag of in the tag pool, not the object's tag itself
        static void ReplaceTag(std::string tagName, GameObject* gameObj);

        //* getter Funcs

        // get a tag from a object in the tag pool
        static std::string GetTagByGameObject(GameObject* gameObj);

        // get objects from the tag pool by tag
        static std::vector<GameObject*> GetObjectsByTag(std::string tagName);

        // check if tag pertains to a passed object that exists in tag pool
        static bool CheckObjectByTag(std::string target, GameObject* gameObj);

        // get amount of objects in the tag system
        static int GetAmountOfObjects();

        //* remover Funcs

        // get object and remove from list
        static void RemoveObject(GameObject* gameObj);

        // get and remove objects with a certain tag
        static void RemoveObjectsWithTag(std::string& tagName);

        // clear tag pool of reference to objects
        static void Clear();

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