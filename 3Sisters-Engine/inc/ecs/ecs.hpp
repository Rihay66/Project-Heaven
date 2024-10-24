#pragma once

#ifndef ECS_HPP
#define ECS_HPP

#include <type_traits>

#include <ecs/managers/entity_manager.hpp>
#include <ecs/managers/component_manager.hpp>
#include <ecs/managers/system_manager.hpp>

/* A static singleton ECS (aka coordinator) class that hosts
 several function to create, manage, remove Entities, Components,
 and Systems. 
*/
class ECS{
    public:
        /* initialize the entity, component, and system managers
            this function also contains debug options
            d - debug, debug outputs, error checking
            r - release, skip most functional error checking and some debug outputs (use )
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
            
            //? check if component is not registered
            if(componentManager->GetComponentType<T>() == 255){
                std::cout << "ERROR: Failed to add component to entity: " <<  entity << " | component: " << typeid(T).name() << " isn't registered to ECS!" << "\n";
                return;
            }
            // else add component to existing entity

            componentManager->AddComponent<T>(entity,component);

            Signature signature = entityManager->GetSignature(entity); 
            signature.set(componentManager->GetComponentType<T>(), true);
            entityManager->SetSignature(entity, signature);

            systemManager->EntitySignatureChange(entity, signature);
        }

        // remove a component from an existing entity
        template<typename T>
        static void RemoveComponent(Entity entity){

            //? check if component is not registered
            if(componentManager->GetComponentType<T>() == 255){
                std::cout << "ERROR: Failed to remove component to entity: " <<  entity << " | component: " << typeid(T).name() << " isn't registered to ECS!" << "\n";
                return;
            }

            componentManager->RemoveComponent<T>(entity);

            Signature signature = entityManager->GetSignature(entity);
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

        /* set the signatures that a system can use for in the entities

        */
        template<typename T>
        static void SetSystemSignature(Signature signature){
            systemManager->SetSignature<T>(signature);
        }

        /* set the signatures that a system can use for in the entities
            
        */
        template<typename T, typename... Args>
        static void SetSystemSignature(Args... args){
            // check if args are of type ComponentType
            static_assert((std::is_same_v<Args, ComponentType> && ...), "ERROR: Invalid signature argument as all component types are of std::uint8_t"); 
            
            // check the amount of arguments to the max components
            static_assert(sizeof...(args) < MAX_COMPONENTS, "ERROR: Too many specified signature component types, the max is 32");

            // create signature to fill
            Signature sig;
            // get value and grab amount of all arguments
            ComponentType arguments[] = { args... };

            // loop through all arguments and populate signature
            for(int i = 0; i < sizeof...(args); i++){
                sig.set(arguments[i]);
            }

            systemManager->SetSignature<T>(sig);
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