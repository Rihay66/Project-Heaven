#pragma once

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <gameObjs/rigidbodyObject.hpp>
#include <SDL2/SDL_events.h>

//Player class with inheritence from GameObject
class Player : public physicsObject{
    public:
        //declare const vars
        //glm dir
        const glm::vec2 glmUp = glm::vec2(0.0f, 1.0f);
        const glm::vec2 glmRight = glm::vec2(1.0f, 0.0f);
        //box2D dir
        const b2Vec2 b2Up = {0.0f, 1.0f};
        const b2Vec2 b2Right = {1.0f, 0.0f};

        //reference to the SDL event, meant to be replaced 
        SDL_Event eventHandle;

        //Reference to the deltatime, meant to be replaced
        float deltatime = 0;

        //movement
        float speed;
        //controller enable
        bool isController;
        //controller joystick deadzone
        float controllerDeadZone;

        //deltatime
        float currentDeltaTime = 1.0f;

        //Used to check for debug mode
        bool isDebug = false;

        //constructor / desctructor
        Player(glm::vec2 pos, glm::vec2 siz, int sprt, float speed = 1.0f, float conDeadzone = 0.0f, bool destroyed = false, glm::vec3 clr = glm::vec3(1.0f));
        ~Player();

        //input function
        b2Body* physicBody();
};

#endif // __PLAYER_H__