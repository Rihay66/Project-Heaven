#pragma once

#ifndef GAMEHANDLER_HPP
#define GAMEHANDLER_HPP

#include <iostream>
#include <algorithm>

#include <resourceSys/resourceManager.hpp>
#include <engine/physics.hpp>
#include "../inc/player.hpp"
#include <orthoCam/camera.hpp>
#include <engine/renderer.hpp>
#include <glm/glm.hpp>

//define global vars for objects to use
const float PlayerSpeed(250.0f);
const glm::vec2 standardSpriteSize(1.0f, 1.0f);
const glm::vec2 defaultModelSize(50.0f, 150.0f);
const glm::vec2 smallModelSize(40.0f, 120.0f);

//Define game states
enum GAMESTATE{
    GAME_ACTIVE, GAME_DEBUG, GAME_MENU, GAME_CUTSCENE
};
//define controller state
enum CONTROLSSTATE{
    KEYBOARDMOUSE, KMCONTROLLER
};

//handler class that manages all objects and also make use of the resource manager
class gameHandler{
    private:
        //Contain reference of the window size
        unsigned int Width, Height;

        //contain physics 
        Physics* phys;
        //contain renderer
        Renderer* renderer;

    public:
        //Reference to the SDL even handle
        SDL_Event eventHandle;
        //Game state & input state
        GAMESTATE Game_State;
        CONTROLSSTATE Controller_State;
        void setGameState(int i);
        void setControllerState(int i);
        //Game elements & values
        std::vector<GameObject*> renderList;

        gameHandler(unsigned int width, unsigned int height);
        ~gameHandler();

        void init(); //intializes game (loads all shaders/textures/levels/gameobjects/camera/etc)
        void update(float deltaTime);
        void render();
};

#endif