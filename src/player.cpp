#include "../inc/player.h"

Player::Player() : speed(0.0f), dir(UP){}

Player::Player(glm::vec2 pos, glm::vec2 siz, Texture2D sprt, float spd, glm::vec3 color) : GameObject(pos, siz, sprt, color), speed(spd), dir(UP){
    //set any non static var from gameobject class
    this->collidable = true;
}

void Player::playerInput(float deltaTime, GLFWwindow* &window){
    //move the player
    float movement = this->speed * deltaTime;

    //input for movement
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        //move up
        position -= movement * up * 3.0f;
        //set state
        dir = UP;
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        //move down
        position += movement * up * 3.0f;
        //set state
        dir = DOWN;
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        //move left
        position -= movement * right;
        //set state
        dir = LEFT;
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        //move right
        position += movement * right;
        //set state
        dir = RIGHT;
    }
}