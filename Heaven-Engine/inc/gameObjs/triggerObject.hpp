#pragma once

#ifndef TRIGGEROBJECT_HPP
#define TRIGGEROBJECT_HPP

#include <gameObjs/gameObject.hpp>
#include <resourceSys/componentUtils.hpp>
#include <resourceSys/tagSystem.hpp>

/* Deriving Class of GameObject
*/
class TriggerObject : public GameObject{
    private:
        // declare local variables that are used by the virtual triggers
        int currentTimeToTrigger = 0;
        // this value is used to set as a timer interval to call onTriggerSta()
        int maxTimeToTrigger;

    protected:
        // store last object to collide
        std::vector<GameObject*> collidedObjs;
        // declare trigger type
        TriggerType trigType;
        // define function to check if a object already exists in the passed list
        bool isAlreadyPresent(const std::vector<GameObject*>& vec, GameObject* value);

    public:
        // constructor
        TriggerObject(int sprt, glm::vec2 pos = glm::vec2(0.0f), glm::vec2 siz = glm::vec2(1.0f), glm::vec4 color = glm::vec4(1.0f));
        // destructor
        ~TriggerObject();
        
        //* Getter Functions
        // returns this object's current Trigger type
        TriggerType getTriggerType();

        //* Setter Functions
        /* set the max time to trigger for the onTriggerStay()
        * NOTE: Can't be less than 1
        */
        void setTimeToTrigger(int amount);

        //* Virtual Functions
        /* called to check for trigger type and do a overwritten action
        * NOTE: It is possible to mix different trigger types
        */
        virtual void triggerCollisionCallback(GameObject* obj);
        // used to define any function to do when this object is triggered

        /* used when a physics object immediately collides with this object
        * NOTE: Requires Trigger type to be Enter
        */
        virtual void onTriggerEnter(GameObject* obj){return;}
        /* used when a physics object stays colliding with this object for a certain amount of time
        * NOTE: Requires Trigger type to be Stay
        */
        virtual void onTriggerStay(GameObject* obj){return;}
        /* used when a physics object had collided with this object
        * NOTE: Requires Trigger type to be Exit
        */
        virtual void onTriggerExit(GameObject* obj){return;} 

        //* Helper Functions

        // define a function that checks objects that last collided if this objects is a Exit trigger
        void exitTriggerObjectCheck();
};  

#endif