#pragma once

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "../inc/rigidbodyObject.hpp"
#include <GLFW/glfw3.h>

//future use for changing sprite
enum Direction{
    UP, DOWN, LEFT, RIGHT
};

//Player class with inheritence from GameObject
class Player : public physicsObject{
    public:
        //declare const vars
        const glm::vec2 up = glm::vec2(0.0f, 1.0f);
        const glm::vec2 right = glm::vec2(1.0f, 0.0f);

        //declare direction enum
        Direction dir;

        //movement
        float speed;

        //constructors
        Player(glm::vec2 pos, glm::vec2 siz, int sprt, float speed = 1.0f, glm::vec3 clr = glm::vec3(1.0f));

        //input function
        void playerInput(float deltaTime, GLFWwindow* &window, bool isController, float controllerDeadZone);
};

#endif // __PLAYER_H__