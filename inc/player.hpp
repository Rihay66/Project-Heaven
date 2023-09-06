#pragma once

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../inc/rigidbodyObject.hpp"
#include <box2d/b2_body.h>
#include <GLFW/glfw3.h>

//Player class with inheritence from GameObject
class Player : public physicsObject{
    public:
        //reference to the rigidbody runtime body
        b2Body* body = nullptr;

        //declare const vars
        //glm dir
        const glm::vec2 glmUp = glm::vec2(0.0f, 1.0f);
        const glm::vec2 glmRight = glm::vec2(1.0f, 0.0f);
        //box2D dir
        const b2Vec2 b2Up = {0.0f, 1.0f};
        const b2Vec2 b2Right = {1.0f, 0.0f};

        //movement
        float speed;

        //constructor / desctructor
        Player(glm::vec2 pos, glm::vec2 siz, int sprt, float speed = 1.0f, bool destroyed = false, glm::vec3 clr = glm::vec3(1.0f));
        ~Player();

        //input function
        void playerInput(float deltaTime, GLFWwindow* &window, bool isController, float controllerDeadZone);
};

#endif // __PLAYER_H__