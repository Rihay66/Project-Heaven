#include "../inc/player.hpp"

Player::Player() : speed(0.0f), dir(UP){}

Player::Player(glm::vec2 pos, float siz, Texture2D sprt, float spd, glm::vec3 color) : GameObject(pos, siz, sprt, color), speed(spd), dir(DOWN){
    //set any non static var from gameobject class
    this->collidable = true;
}

void Player::playerInput(float deltaTime, GLFWwindow* &window, bool isController, float controllerDeadZone){ 
    //move the player
    float movement = this->speed * deltaTime;

    //input for movement
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        //move up
        position -= movement * up;
        //set state
        dir = UP;
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        //move down
        position += movement * up;
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

    if(isController && glfwJoystickPresent(GLFW_JOYSTICK_1) == true){
        int axesCount;
        //use axes for movement
        const float* axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);

        //input for movement
        if(axes[0] < -controllerDeadZone){ //left
            //move left
            position -= movement * right;
            //set state
            dir = LEFT;
        }
        if(axes[0] > controllerDeadZone){ //right
            //move right
            position += movement * right;
            //set state
            dir = RIGHT;
        }
        if(axes[1] < -controllerDeadZone){ //up
            //move up
            position -= movement * up;
            //set state
            dir = UP;
        }  
        if(axes[1] > controllerDeadZone){ //down
            //move down
            position += movement * up;
            //set state
            dir = DOWN;
        }
    }
}