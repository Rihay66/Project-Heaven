#pragma once

#ifndef ECS_HPP
#define ECS_HPP

#include <ecs/managers/entity_manager.hpp>
#include <ecs/managers/component_manager.hpp>
#include <ecs/managers/system_manager.hpp>

/* ECS (aka coordinator)
*/
class ECS{
    public:
        /* initialize the entity, component, and system managers
            this function also contains debug options
            d - default, no debug outputs
            r - repeats, outputs msg when function is called more than once
        */
        static void Init(char debugOption = 'd');

        //* Entity Functions

        // create an Entity, returns reference of created Entity
        static Entity CreateEntity();

        // destroy given Entity and remove attached components
        void DestroyEntity(Entity entity);

        //* Component Functions
        
        // register specified component for entity and system usage
        template<typename T>
        static void RegisterComponent(){
            componentManager->RegisterComponent<T>();
        }     

        // add a specified component to an existing entity 
        template<typename T>
        static void AddComponent(Entity entity, T component){
            componentManager->AddComponent<T>(entity,component);

            const auto& signature = entityManager->GetSignature(entity); 
            signature.set(componentManager->GetComponentType<T>(), true);
            entityManager->SetSignature(entity, signature);

            systemManager->EntitySignatureChange(entity, signature);
        }

        // remove a component from an existing entity
        template<typename T>
        static void RemoveComponent(Entity entity){
            componentManager->RemoveComponent<T>(entity);

            const auto& signature = entityManager->GetSignature(entity);
            signature.set(componentManager->GetComponentType<T>(), false);
            entityManager->SetSignature(entity, signature);

            systemManager->EntitySignatureChange(entity, signature);
        }

        // get reference of an exiting entity's component
        template<typename T>
        static T& GetComponent(Entity entity){
            return componentManager->GetComponent<T>(entity);
        }

        // get component type of given component
        template<typename T>
        static ComponentType GetComponentType(){
            return componentManager->GetComponentType<T>();
        }

        //* System Functions

        // register a system, returns system reference for external use
        template<typename T>
        static std::shared_ptr<T> RegisterSystem(){
            return systemManager->RegisterSystem<T>();
        }

        template<typename T>
        static void SetSystemSignature(Signature signature){
            systemManager->SetSignature<T>(signature);
        }

    private:
        // private constructor
        ECS() {}
        // private pointer storage of the entity manager
        static std::unique_ptr<EntityManager> entityManager;

        // private pointer storage of the component manager
        static std::unique_ptr<ComponentManager> componentManager;

        // private pointer storage of the system manager
        static std::unique_ptr<SystemManager> systemManager;

};

#endif