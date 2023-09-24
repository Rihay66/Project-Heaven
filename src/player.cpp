#include "../inc/player.hpp"

Player::Player(GLFWwindow* &handle, glm::vec2 pos, glm::vec2 siz, int sprt, float spd, float cDeadzone, bool destroyed, glm::vec3 color) : 
physicsObject(pos, siz, sprt, color, destroyed, false), speed(spd), window(handle), controllerDeadZone(cDeadzone), isController(false){
    //set any non static var from gameobject or rigidbody class
    
    //set up default rb
    this->rb.Type = BodyType::Dynamic;
    this->rb.fixedRotation = true;
}

Player::~Player(){
    //delete any pointers
    //delete body;
}

b2Body* Player::physicBody(){
    
    b2Body* body = (b2Body*)rb.runtimeBody;

    //Stop any movement when debug is enabled
    if(isDebug)
        return body;

    //move the player
    float movement = this->speed * currentDeltaTime;

    //input for movement
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
        //move up
        //position += movement * up;
        body->ApplyForce({0.0f, movement}, body->GetWorldCenter(), true);
        //set state
        dir = UP;
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS  || glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
        //move down
        //position -= movement * up;
        body->ApplyForce({0.0f, -movement}, body->GetWorldCenter(), true);
        //set state
        dir = DOWN;
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS  || glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
        //move left
        //position -= movement * right;
        body->ApplyForce({-movement, 0.0f}, body->GetWorldCenter(), true);
        //set state
        dir = LEFT;
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS  || glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
        //move right
        //position += movement * right;
        body->ApplyForce({movement, 0.0f}, body->GetWorldCenter(), true);
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
            body->ApplyForce({-movement, 0.0f}, body->GetWorldCenter(), true);
            //set state
            dir = LEFT;
        }
        if(axes[0] > controllerDeadZone){ //right
            //move right
            body->ApplyForce({movement, 0.0f}, body->GetWorldCenter(), true);
            //set state
            dir = RIGHT;
        }
        if(axes[1] < -controllerDeadZone){ //up
            //move up
            body->ApplyForce({0.0f, movement}, body->GetWorldCenter(), true);
            //set state
            dir = UP;
        }  
        if(axes[1] > controllerDeadZone){ //down
            //move down
            body->ApplyForce({0.0f, -movement}, body->GetWorldCenter(), true);
            //set state
            dir = DOWN;
        }
    }

    return body;
}