#pragma once

#ifndef TAG_MANAGER_HPP
#define TAG_MANAGER_HPP

// include standard libraries
#include <map>
#include <memory>
#include <any>
#include <typeinfo>
#include <stdexcept>
#include <string> 
#include <cstring>
//? debug print
#include <iostream>

/* A Static singleton TagSystem class that hosts several
 functions to add, edit, find GameObjects that have a set tag 
 to a static tag pool. All functions and tag pool are static.
 This Class has no public constructor defined.
*/
class TagManager{
    public:
        //* adder Funcs

        // add a tag and object to the resource pool, if object already exists then replace it's tag
        template<typename T>
        static void AddTag(const std::string& tag, T& t){
            tagPool.insert({tag, std::make_pair(std::make_shared<std::reference_wrapper<T>>(t), typeid(T).name())});    
        }

        //* getter Funcs

        // get the object associated with type
        template<typename T>
        static T& GetTag(const std::string& tag){
            //TODO: Optimize finding the key, maybe switch the tagPool to a vector<>

            //TODO: Optimize search for tag and type

            // iterate through the map
            auto const& iter = tagPool.find(tag);
            // check iteration
            if(iter == tagPool.end()){
                // throw error that it couldn't be found
                throw std::runtime_error("ERROR: Tag not found");
            }

            // handle any bad casting
            const char* typeName = typeid(T).name();
            for(auto const& pair : tagPool){
                if(pair.first.compare(tag) == 0 && std::strcmp(typeName, pair.second.second) == 0){
                    return std::any_cast<std::shared_ptr<std::reference_wrapper<T>>>(pair.second.first)->get();
                } 
            }

            throw std::runtime_error("ERROR: Type mismatch!");
        }

        // get a tag from a object in the tag pool
        //static std::string GetTagByGameObject(GameObject* gameObj);

        // get objects from the tag pool by tag
        //static std::vector<GameObject*> GetObjectsByTag(std::string tagName);

        // check if tag pertains to a passed object that exists in tag pool
        //static bool CheckObjectByTag(std::string target, GameObject* gameObj);

        // get amount of objects in the tag system
        //static int GetAmountOfObjects();

        //* helper Funcs
        
        // get object from the list and replace the tag of in the tag pool, not the object's tag itself
        //static void ReplaceTag(std::string tagName, GameObject* gameObj);

        //* remover Funcs

        // get object and remove from list
        //static void RemoveObject(GameObject* gameObj);

        // get and remove objects with a certain tag
        //static void RemoveObjectsWithTag(std::string& tagName);

        // clear tag pool of reference to objects
        static void Clear();

    private:
        // static resource. Contains reference alongside with their assigned tag

        static std::multimap<std::string, std::pair<std::any, const char*>> tagPool;

        // private constructor
        TagManager(){}

        //! Currently EXPERIMENTAL, may cause exceptions or segfaults
        // private boolean to track automatic clear()
        static bool isAutoClearSet;
        // set up automatic de-allocation of loaded resources
        static void SetUpAutoClear();
};
#endif