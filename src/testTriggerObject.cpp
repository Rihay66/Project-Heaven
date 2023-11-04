#include "../inc/testTriggerObject.hpp"
#include <stdio.h>

TestTriggerObject::TestTriggerObject(glm::vec2 pos, glm::vec2 siz,int sprt, glm::vec4 color) : TriggerObject(pos, siz, sprt, color){

}

void TestTriggerObject::onTriggerEnter(GameObject* obj){
    //Check if object is the player
    if(TagSystem::getObject("Player") == obj){
        //Do something...
        printf("TRIGGERED!!!\n");
    }
}