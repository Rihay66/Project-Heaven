#include <ecs/ecs.hpp>

//? include standard library for debug outputs
#include <iostream>

// initialize static variables
std::unique_ptr<EntityManager> ECS::entityManager;
std::unique_ptr<ComponentManager> ECS::componentManager;
std::unique_ptr<SystemManager> ECS::systemManager;

void ECS::Init(char debugOption){
    // check each ECS manager if they've been initialized

    //TODO: Find a cleaner way to avoid reinitialization of each manager

    if(entityManager.get() == nullptr){
        entityManager = std::make_unique<EntityManager>();
    }else {
        if(debugOption == 'r')
            std::cout << "ERROR: ECS being initialized more than once!\n";
        return;
    }

    if(componentManager.get() == nullptr){
        componentManager = std::make_unique<ComponentManager>();
    }else {
        if(debugOption == 'r')
            std::cout << "ERROR: ECS being initialized more than once!\n";
        return;
    }

    if(systemManager.get() == nullptr){
        systemManager = std::make_unique<SystemManager>();
    }else {
        if(debugOption == 'r')
            std::cout << "ERROR: ECS being initialized more than once!\n";
        return;
    }
}

Entity ECS::CreateEntity(){
    return entityManager->CreateEntity();
}

void ECS::DestroyEntity(Entity entity){
    entityManager->DestroyEntity(entity);

    componentManager->EntityDestroyed(entity);

    systemManager->EntityDestroyed(entity);
}

