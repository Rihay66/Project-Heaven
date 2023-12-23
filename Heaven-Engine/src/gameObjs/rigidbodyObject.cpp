#include <gameObjs/rigidbodyObject.hpp>

PhysicsObject::PhysicsObject(glm::vec2 pos, glm::vec2 size, int sprt, glm::vec4 color, bool destroyed) : 
GameObject(pos, size, sprt, color), isDestroyed(destroyed){}