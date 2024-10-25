#include <resourceSystems/managers/tag_manager.hpp>

// instantiate static resources
std::multimap<std::string, std::pair<std::any, const char*>>            TagManager::tagPool;

int TagManager::GetAmountOfObjects(){
    // exit function if the list is empty
    if(tagPool.size() <= 0)
        return -1; // stop function from here

    // return amount objects
    return tagPool.size();
}