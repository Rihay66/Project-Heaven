#include "../inc/player.hpp"

Player::Player(glm::vec2 pos, glm::vec2 siz, int sprt, float spd, bool destroyed, glm::vec3 color) : physicsObject(pos, siz, sprt, color, destroyed, false), speed(spd){
    //set any non static var from gameobject or rigidbody class
    
    //set up default rb
    this->rb.Type = BodyType::Dynamic;
    this->rb.fixedRotation = true;

    //Get rb runtime body
    this->body = (b2BodyDef*)rb.runtimeBody;
}

Player::~Player(){
    //delete any pointers
    delete body;
}

void Player::playerInput(float deltaTime, GLFWwindow* &window, bool isController, float controllerDeadZone){ 
    //move the player
    float movement = this->speed * deltaTime;

    //TODO: Replace the movement with box2d way of moving dynamic objects

    //input for movement
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        //move up
        position += movement * up;
        //set state
        dir = UP;
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        //move down
        position -= movement * up;
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
            position += movement * up;
            //set state
            dir = UP;
        }  
        if(axes[1] > controllerDeadZone){ //down
            //move down
            position -= movement * up;
            //set state
            dir = DOWN;
        }
    }
}