#pragma once

#ifndef COMPONENT_MANAGER_HPP
#define COMPONENT_MANAGER_HPP

#include <memory>
#include <unordered_map>

#include <ecs/types/entity.hpp>
#include <ecs/types/component.hpp>
#include "ecs/types/component_array.hpp"

/* Component Manager manages the interaction between
all of the different component arrays when a component
needs to be removed or added.
*/
class ComponentManager{
    private:
        // map from the type string pointer to a component type
        std::unordered_map<const char*, ComponentType> componentTypes{};

        // map from the type string pointer to a component array
        std::unordered_map<const char*, std::shared_ptr<IComponentArray>> componentArrays{};

        // the component type to be assigned to the next registered component, starting from 0
        ComponentType nextComponentType{};

        // helper function to get the statically caster pointer to the component array of generic type T
    	template<typename T>
	    std::shared_ptr<ComponentArray<T>> GetComponentArray()
	    {
		    const char* typeName = typeid(T).name();

		    if(componentTypes.find(typeName) == componentTypes.end()){
                return nullptr;
            }

		    return std::static_pointer_cast<ComponentArray<T>>(componentArrays[typeName]);
	    }

    public:
        // registers a new component to be tracked
        template<typename T>
        void RegisterComponent(){
            const char* typeName = typeid(T).name();

            if(componentTypes.find(typeName) != componentTypes.end()){
                return;
            }

            // add this component type to the component type map
            componentTypes.insert({typeName, nextComponentType});

            // create a component array pointer and add it to the component arrays map
            componentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});

            // increment the value so that the next component registered will be different
            nextComponentType++;
        }

        // get component type of a existing component
        template<typename T>
        ComponentType GetComponentType(){
            const char* typeName = typeid(T).name();

            if(componentTypes.find(typeName) == componentTypes.end()){
                return -1;
            }

            // return this component's type
            return componentTypes[typeName];
        }

        // add a component to the array for an entity
        template<typename T>
        void AddComponent(Entity entity, T component){
            GetComponentArray<T>()->InsertData(entity, component);
        }

        // remove a component from the array for an entity
        template<typename T>
        void RemoveComponent(Entity entity){
            GetComponentArray<T>()->RemoveData(entity);
        }

        // return a reference to a component from the array for an entity
        template<typename T>
        T& GetComponent(Entity entity){
            return GetComponentArray<T>()->GetData(entity);
        }

        /* notify all component arrays that given entity is destroyed
         and remove attached components
        */
        void EntityDestroyed(Entity entity){
            for(auto const& pair : componentArrays){
                // call interface of component to remove relavent component from entity
                pair.second->EntityDestroyed(entity);
            }
        }
};

#endif