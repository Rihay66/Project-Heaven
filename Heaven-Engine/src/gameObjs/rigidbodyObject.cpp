#include <gameObjs/rigidbodyObject.hpp>

PhysicsObject::PhysicsObject(int sprt, glm::vec2 pos, glm::vec2 size, glm::vec4 color ,bool interpolation, bool destroyed) : 
GameObject(sprt, pos, size, color, interpolation), isDestroyed(destroyed){}