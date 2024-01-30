#include <gameObjs/gameObject.hpp>

GameObject::GameObject(int sprt, glm::vec2 pos, glm::vec2 siz, glm::vec4 col, bool inter) 
: position(pos), size(siz), color(col), textureIndex(sprt), rotation(0.0f), tag("default"), renderType(RenderType::Default), interpolation(inter) {}

//Define getter functions
bool GameObject::getInterpolationFlag(){
    return this->interpolation;
}