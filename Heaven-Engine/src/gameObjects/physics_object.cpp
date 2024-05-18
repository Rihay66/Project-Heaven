#include <gameObjects/physics_object.hpp>

PhysicsObject::PhysicsObject(int sprt, glm::vec2 pos, glm::vec2 size, glm::vec4 color ,bool interpolation, bool destroyed) : 
GameObject(sprt, pos, size, color, interpolation), isDestroyed(false){}

void PhysicsObject::Destroy(){
    this->isDestroyed = true;
}

bool PhysicsObject::getDestroyedStatus(){
    return this->isDestroyed;
}