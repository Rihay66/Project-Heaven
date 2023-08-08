#include "../inc/gameObject.hpp"

GameObject::GameObject() 
    : position(0.0f, 0.0f), size(1.0f), color(1.0f), rotation(0.0f), sprite(), destroyed(false), collidable(false) { }

GameObject::GameObject(glm::vec2 pos, float siz, Texture2D sprt, glm::vec3 col) : position(pos), size(siz), color(col), sprite(sprt), rotation(0.0f), destroyed(false), collidable(false) {}