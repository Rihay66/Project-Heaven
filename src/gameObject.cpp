#include "../inc/gameObject.hpp"

GameObject::GameObject(glm::vec2 pos, glm::vec2 siz, int sprt, glm::vec3 col) 
: position(pos), size(siz), color(col), textureIndex(sprt), rotation(0.0f) {}