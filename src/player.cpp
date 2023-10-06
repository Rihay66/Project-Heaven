#include "../inc/player.hpp"

Player::Player(glm::vec2 pos, glm::vec2 siz, int sprt, float spd, float cDeadzone, bool destroyed, glm::vec3 color) : physicsObject(pos, siz, sprt, color, destroyed, false), speed(spd), controllerDeadZone(cDeadzone), isController(false){
    // set any non static var from gameobject or rigidbody class

    // set up default rb
    this->rb.Type = BodyType::Dynamic;
    this->rb.fixedRotation = true;
}

Player::~Player(){
    // delete any pointers
    // Remove controller
    if (this->joystick != nullptr){
        SDL_GameControllerClose(joystick);
    }
}

b2Body *Player::physicBody(){

    b2Body *body = (b2Body *)rb.runtimeBody;

    // Stop any movement when debug is enabled
    if (isDebug)
        return body;

    // move the player
    // Check if a key being pressed
    float movement = this->speed * deltatime;

    // Check for controller is enabled and check for input
    if (isController && joystick != nullptr){
        SDL_GameControllerUpdate();
        if (SDL_GameControllerGetAxis(joystick, SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX) > controllerDeadZone){
            printf("Right\n");
        }
        if (SDL_GameControllerGetAxis(joystick, SDL_GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX) < -controllerDeadZone){
            printf("Left\n");
        }
    }
    else if(!isController){
        //Get key board states
        state = SDL_GetKeyboardState(NULL);

        // Update physics according to direction
        if (state[SDL_SCANCODE_W] > 0 || state[SDL_SCANCODE_UP] > 0)
        {
            // move up
            body->ApplyForce({0.0f, movement}, body->GetWorldCenter(), true);
        }
        if (state[SDL_SCANCODE_S] > 0 || state[SDL_SCANCODE_DOWN] > 0)
        {
            // move down
            body->ApplyForce({0.0f, -movement}, body->GetWorldCenter(), true);
        }
        if (state[SDL_SCANCODE_A] > 0 || state[SDL_SCANCODE_LEFT] > 0)
        {
            // move left
            body->ApplyForce({-movement, 0.0f}, body->GetWorldCenter(), true);
        }
        if (state[SDL_SCANCODE_D] > 0 || state[SDL_SCANCODE_RIGHT] > 0)
        {
            // move right
            body->ApplyForce({movement, 0.0f}, body->GetWorldCenter(), true);
        }
    }

    return body;
}