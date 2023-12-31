#pragma once

#ifndef TRIGGEROBJECT_HPP
#define TRIGGEROBJECT_HPP

#include <gameObjs/gameObject.hpp>
#include <resourceSys/componentUtils.hpp>
#include <resourceSys/tagSystem.hpp>

class TriggerObject : public GameObject{
    private:
        //declare local variables that are used by the virtual triggers
        int currentTimeToTrigger = 0;

    public:
        //Declare trigger type
        TriggerType trigType;

        //Used to check if object is enabled and when disabled is automatically removed from game
        bool isDestroyed; 
        //This value is used to set as a timer interval to call onTriggerSta()
        int maxTimeToTrigger;

        //Store last object to collide
        std::vector<GameObject*> collidedObjs;

        //Define function to check if a object already exists in the passed list
        bool isAlreadyPresent(const std::vector<GameObject*>& vec, GameObject* value);

        //Define a function that checks objects that last collided if this objects is a EXIT TRIGGER
        void exitTriggerObjectCheck();

        //Constructor
        TriggerObject(int sprt, glm::vec2 pos = glm::vec2(0.0f), glm::vec2 siz = glm::vec2(1.0f), glm::vec4 color = glm::vec4(1.0f));
        //Destructor
        ~TriggerObject();
        
        //Called to check for trigger type and do a overwritten action
        virtual void triggerCollisionCallback(GameObject* obj);
        //Used to define any function to do when this object is triggered
        virtual void onTriggerEnter(GameObject* obj){return;}
        virtual void onTriggerStay(GameObject* obj){return;}
        virtual void onTriggerExit(GameObject* obj){return;} 
};  

#endif