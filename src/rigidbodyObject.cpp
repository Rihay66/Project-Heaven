#include "../inc/rigidbodyObject.hpp"

physicsObject::physicsObject(glm::vec2 pos, glm::vec2 size, int sprt, bool destroyed, bool trigger, glm::vec3 color) : GameObject(pos, size, sprt, color), isDestroyed(destroyed), isTrigger(trigger){}