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
#include <vector>
#include <functional>

/* A Static singleton TagSystem class that hosts several
 functions to add, edit, find arbitrary types that have a set tag 
 to a static tag pool.
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

        /* get a list of all of given type with given tag
        ! Throws runtime errors
        */
        template<typename T>
        static std::vector<std::reference_wrapper<T>> GetAllWithTag(const std::string& tag){
            //TODO: Optimize finding the key, maybe switch the tagPool to a vector<>
            
            // check if map is not empty
            if(tagPool.empty()){
                throw std::runtime_error("ERROR: Tag pool empty!");
            }

            // iterate through the map
            auto const& iter = tagPool.find(tag);
            // check iteration
            if(iter == tagPool.end()){
                // throw error that it couldn't be found
                throw std::runtime_error("ERROR: Tag not found");
            }

            // grab the type name
            const char* typeName = typeid(T).name();
            // create list to store references to variables or objects
            std::vector<std::reference_wrapper<T>> tempList;
           
            //TODO: Optimize search for tag and type

            // iterate through the map and find the element
            for(auto const& pair : tagPool){
                if(pair.first.compare(tag) == 0 && std::strcmp(typeName, pair.second.second) == 0){
                    tempList.push_back(std::any_cast<std::shared_ptr<std::reference_wrapper<T>>>(pair.second.first)->get());
                } 
            }

            // check if list is not empty
            if(!tempList.empty()){
                return tempList;
            }

            // else throw a mismatch error
            throw std::runtime_error("ERROR: List being retrieved is empty by either Type mismatched or object doesn't exist!");
        }

        // get a tag from a exisiting variable or object in the tag pool
        template<typename T>
        static std::string GetTagOfElement(T& ref){
            // iterate through the tag pool
            for(auto iter = tagPool.begin(); iter != tagPool.end(); iter++){
                try{
                    // grab each element's std::shared_ptr

                    // grab the std::shared_ptr of iteration
                    auto& temp = 
                        std::any_cast<std::shared_ptr<std::reference_wrapper<T>>>(iter->second.first)->get();

                    // check if both given variable or object and tag pool have the same reference
                    if(std::addressof(temp) == std::addressof(ref)){
                        return iter->first;
                    }

                }catch(const std::bad_any_cast&){
                    // skip iteration
                    continue;
                }
            }

            return "";
        }

        // check if tag pertains to a variable or object that exists in tag pool
        template<typename T>
        static bool CheckElementByTag(const std::string& target, T& ref){
            // iterate through the tag pool
            for(auto iter = tagPool.begin(); iter != tagPool.end(); iter++){
                try{
                    // grab each element's std::shared_ptr

                    // grab the std::shared_ptr of iteration
                    auto& temp = 
                        std::any_cast<std::shared_ptr<std::reference_wrapper<T>>>(iter->second.first)->get();
                    
                    // check if it has the same tag and tag pool iteration have the same reference
                    if(target.compare(iter->first) == 0 && std::addressof(temp) == std::addressof(ref)){
                        return true;
                    }

                }catch(const std::bad_any_cast&){
                    // skip iteration
                    continue;
                }
            }

            return false;
        }

        // get amount of objects in the tag system
        static int GetAmountOfObjects();

        //* helper Funcs
        
        /* get variable or object from the list and replace the tag of in the tag pool
        * NOTE: The type's tag being replaced causes all of the type's previous tag to be removed 
        */
        template<typename T>
        static void ReplaceElementTag(const std::string& tagName, T& ref){
            // find object and remove completely from tag pool
            if(TagManager::RemoveObject(ref)){
                // add as a new object
                TagManager::AddTag(tagName, ref);
            }else{
                // throw an error
                throw std::runtime_error("ERROR: Couldn't find variable or object in tag pool!");
            }
        }

        //* remover Funcs

        // get object reference and remove from list, returns true if object was succesfully removed and false otherwise
        template<typename T>
        static bool RemoveObject(T& ref){
            // create boolean
            bool state = false;

            // iterate through the map
            for(auto iter = tagPool.begin(); iter != tagPool.end();){
                try{
                    // grab each element's std::shared_ptr

                    // grab the exact reference of iteration
                    auto& temp = 
                        std::any_cast<std::shared_ptr<std::reference_wrapper<T>>>(iter->second.first)->get();
                    
                    // compare if both given reference and element are the same
                    if(std::addressof(temp) == std::addressof(ref)){
                        
                        // reset shared_ptr
                        auto ptr = std::any_cast<std::shared_ptr<std::reference_wrapper<T>>>(iter->second.first);
                        ptr.reset();

                        // erase element from tag pool
                        iter = tagPool.erase(iter);

                        // change state to be true
                        state = true;
                    }

                    // continue loop
                    iter++;
                    
                }catch(const std::bad_any_cast&){
                    // continue loop
                    iter++;
                }
            }

            // return state
            return state;
        }

        // remove elements with the given type and tag
        template<typename T>
        static void RemoveElementsByTag(const std::string& tag){
            // iterate through the map
            for(auto iter = tagPool.begin(); iter != tagPool.end();){
                // check if elements has the given tag and type
                if(iter->first.compare(tag) == 0 && std::strcmp(typeid(T).name(), iter->second.second) == 0){
                    // try to remove element
                    try{
                        // grab the std::shared_ptr of iteration
                        auto ptr = 
                            std::any_cast<std::shared_ptr<std::reference_wrapper<T>>>(iter->second.first);
                        // remove reference to object
                        ptr.reset();

                        // erase element
                        iter = tagPool.erase(iter);

                    }catch(const std::bad_any_cast&){
                        // continue the loop
                        iter++;
                    }
                }else{
                    iter++;
                }
            }
        }

    private:
        // static resource. Contains reference alongside with their assigned tag
        static std::multimap<std::string, std::pair<std::any, const char*>> tagPool;

        // private constructor
        TagManager(){}
};
#endif