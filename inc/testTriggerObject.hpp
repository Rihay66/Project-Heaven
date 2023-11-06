#pragma once

#ifndef TESTTRIGGEROBJECT_HPP
#define TESTTRIGGEROBJECT_HPP

#include <gameObjs/triggerObject.hpp>
#include <resourceSys/tagSystem.hpp>

class TestTriggerObject : public TriggerObject{
    public:
        //contructor
        TestTriggerObject(glm::vec2 pos, glm::vec2 siz, int sprt, glm::vec4 color = glm::vec4(1.0f));

        //Trigger types
        void onTriggerEnter(GameObject* obj) override;
        void onTriggerStay(GameObject* obj) override;
        void onTriggerExit(GameObject* obj) override;

};

#endif