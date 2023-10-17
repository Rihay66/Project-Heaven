#include <gameObjs/rigidbodyObject.hpp>

physicsObject::physicsObject(glm::vec2 pos, glm::vec2 size, int sprt, glm::vec4 color, bool destroyed, bool trigger) : GameObject(pos, size, sprt, color), isDestroyed(destroyed), isTrigger(trigger){
    //Set default value for direction enum
    dir = UP;
}