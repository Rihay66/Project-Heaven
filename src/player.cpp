#include "../inc/player.hpp"

Player::Player(glm::vec2 pos, glm::vec2 siz, int sprt, float spd, float cDeadzone, bool destroyed, glm::vec3 color) : physicsObject(pos, siz, sprt, color, destroyed, false), speed(spd), controllerDeadZone(cDeadzone), isController(false){
    // set any non static var from gameobject or rigidbody class

    // set up default rb
    this->rb.Type = BodyType::Dynamic;
    this->rb.fixedRotation = true;

    // set up default movement flags
    for(int i = 0; i < sizeof(moveFlags) / sizeof(moveFlags[0]); i++){
        moveFlags[i] = false;
    }
}

Player::~Player(){
    // delete any pointers
    // Remove controller
    if (this->joystick != nullptr){
        SDL_GameControllerClose(joystick);
    }
}

//Check for input
void Player::checkInput(SDL_Event handle){
    switch (handle.key.keysym.sym)
    {
    case SDLK_w:
        //move up
        moveFlags[0] = true;
        break;

    case SDLK_s:
        //move down
        moveFlags[1] = true;
        break;

    case SDLK_d:
        //move right
        moveFlags[2] = true;
        break;

    case SDLK_a:
        //move left
        moveFlags[3] = true;
        break;

    default:
        break;
    }
}

//Check for no input, to reset certain values
void Player::checkExitInput(SDL_Event handle){
    switch(handle.key.keysym.sym){
        case SDLK_w:
            //stop moving up
            moveFlags[0] = false;
            break;

        case SDLK_s:
            //stop moving down
            moveFlags[1] = false;
            break;

        case SDLK_d:
            //stop moving right
            moveFlags[2] = false;
            break;

        case SDLK_a:
            //stop moving left
            moveFlags[3] = false;
            break;

        default:
            break;
    }
}

b2Body *Player::physicBody(){

    b2Body *body = (b2Body *)rb.runtimeBody;

    // Stop any movement when debug is enabled
    if (isDebug)
        return body;

    //Move the player
    //Calculate movement aoccrding to speed and deltatime
    float movement = this->speed * deltatime;

    //Check for movement flags
    if(moveFlags[0]){
        // move up
        body->ApplyForce({0.0f, movement}, body->GetWorldCenter(), true);
    }
    if(moveFlags[1]){
        // move down
        body->ApplyForce({0.0f, -movement}, body->GetWorldCenter(), true);
    }
    if(moveFlags[2]){
        // move right
        body->ApplyForce({movement, 0.0f}, body->GetWorldCenter(), true);
    }
    if(moveFlags[3]){
        // move left
        body->ApplyForce({-movement, 0.0f}, body->GetWorldCenter(), true);
    }

    return body;
}