#include <gameObjects/game_object.hpp>

#include <glm/trigonometric.hpp>
#include <resourceSystems/tag_system.hpp>

GameObject::GameObject(int sprt, glm::vec2 pos, glm::vec2 siz, glm::vec4 col, bool inter) 
: position(pos), size(siz), color(col), textureIndex(sprt), rotation(0.0f), tag("default"), renderType(RenderType::Default), interpolation(inter) {
    // initialize the interpolation state when true
    if(interpolation){
        // set current state to be current 
        this->currentState.posX = this->position.x;
        this->currentState.posY = this->position.y;
        // set the previous state to be current as well
        this->previousState = this->currentState;
    }
}

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

void GameObject::setRotation(float rot){
    // translate rotation from degrees to radians
    this->rotation = glm::radians(rot);
}

void GameObject::setRotationRadians(float rot){
    // set rotation
    this->rotation = rot;
}

// define getter functions

std::string GameObject::getTag(){
    return this->tag;
}

State& GameObject::getCurrentInterpolatedState(){
    return this->currentState;
}

State&  GameObject::getPreviousInterpolatedState(){
    return this->previousState;
}

bool GameObject::getInterpolationFlag(){
    return this->interpolation;
}

float GameObject::getRotation(){
    return glm::degrees(this->rotation);
}

float GameObject::getRotationRadians(){
    return this->rotation;
}

