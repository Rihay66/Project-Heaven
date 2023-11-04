#pragma once

#ifndef TRIGGEROBJECT_HPP
#define TRIGGEROBJECT_HPP

#include <gameObjs/gameObject.hpp>
#include <resourceSys/componentUtils.hpp>
#include <resourceSys/tagSystem.hpp>

class TriggerObject : public GameObject{
    private:
        //delcare local variables that are used by the virtual triggers
        int maxTimeToTrigger = 5;
        int currentTimeToTrigger = 0;
    public:
        //Declare trigger type
        TriggerType trigType;

        //TODO: USE THIS FOR THE PHYSICS ENGINE
        //declare box collider
        TriggerBoxCollider box; 

        //Used to check if object is enabled and when disabled is automatically removed from game
        bool isDestroyed; 

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