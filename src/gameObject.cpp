#include "../inc/gameObject.h"
GameObject::GameObject() 
    : position(0.0f, 0.0f), size(1.0f, 1.0f), velocity(0.0f), color(1.0f), rotation(0.0f), sprite(), destroyed(false) { }

GameObject::GameObject(glm::vec2 pos, glm::vec2 siz, Texture2D sprt, glm::vec2 vel, glm::vec3 col) : position(pos), size(siz), velocity(vel), color(col), sprite(sprt), rotation(0.0f) {}

void GameObject::Draw2D(Renderer* &renderer)
{
    renderer->Draw2D(this->sprite, this->position, this->size, this->rotation, this->color);
}