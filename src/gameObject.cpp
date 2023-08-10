#include "../inc/gameObject.hpp"

GameObject::GameObject() 
    : position(0.0f, 0.0f), size(1.0f), color(1.0f), rotation(0.0f), textureIndex(0), destroyed(false), collidable(false) { }

GameObject::GameObject(glm::vec2 pos, float siz, int sprt, glm::vec3 col) : position(pos), size(siz), color(col), textureIndex(sprt), rotation(0.0f), destroyed(false), collidable(false) {}