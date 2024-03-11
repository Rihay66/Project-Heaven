#include <gameObjects/game_object.hpp>

#include <resourceSystems/tag_system.hpp>

GameObject::GameObject(int sprt, glm::vec2 pos, glm::vec2 siz, glm::vec4 col, bool inter) 
: position(pos), size(siz), color(col), textureIndex(sprt), rotation(0.0f), tag("default"), renderType(RenderType::Default), interpolation(inter) {}

// define setter functions

void GameObject::setTag(std::string tag){
    this->tag = tag;
    // check if object exists in tag pool
    if(TagSystem::checkObjectByTag(tag, this)){
        // does exist, the replace tag in the tag pool
        TagSystem::replaceTag(tag, this);
    }
}

void GameObject::setCurrentInterpolatedState(State st){
    this->currentState = st;
}

void GameObject::setPreviousInterpolatedState(State st){
    this->previousState = st;
}

// define getter functions

std::string GameObject::getTag(){
    return this->tag;
}

State GameObject::getCurrentInterpolatedState(){
    return this->currentState;
}

State GameObject::getPreviousInterpolatedState(){
    return this->previousState;
}

bool GameObject::getInterpolationFlag(){
    return this->interpolation;
}

