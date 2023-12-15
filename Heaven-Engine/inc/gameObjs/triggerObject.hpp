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
        GameObject* lastObjToCollide;
        //Store target tag 
        std::string targetTag;

        //Constructor
        TriggerObject(glm::vec2 pos, glm::vec2 siz, int sprt, glm::vec4 color = glm::vec4(1.0f));
        
        //Called to check for trigger type and do a overwritten action
        void triggerCollisionCallback(GameObject* obj);
        //Used to define any function to do when this object is triggered
        virtual void onTriggerEnter(GameObject* obj){return;}
        virtual void onTriggerStay(GameObject* obj){return;}
        virtual void onTriggerExit(GameObject* obj){return;} 
};  

#endif