#pragma once

#ifndef GAMEHANDLER_H
#define GAMEHANDLER_H

#include <iostream>
#include <vector>

#include "../inc/resourceManager.hpp"
#include "../inc/player.hpp"
#include "../inc/camera.hpp"
#include "../inc/renderer.hpp"
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

//define global vars for objects to use
const float PlayerSpeed(2.0f);
const glm::vec2 defaultSize(50.0f, 150.0f);
const glm::vec2 smallSize(40.0f, 120.0f);

 //Define game states
enum GAMESTATE{
    GAME_ACTIVE, GAME_DEBUG
};
//define controller state
enum CONTROLSSTATE{
    KEYBOARDMOUSE, KMCONTROLLER
};

//handler class that manages all objects and also make use of the resource manager
class gameHandler{
    private:

        unsigned int Width, Height;
        //contain reference of the window
        GLFWwindow* window;

    public:
        //Game state
        GAMESTATE Game_State;
        CONTROLSSTATE Controller_State;
        void setGameState(int i);
        void setControllerState(int i);
        //Game elements & values
        //std::vector<GameObject> objects;

        gameHandler(unsigned int width, unsigned int height, GLFWwindow* handle);
        ~gameHandler();

        void init(); //intializes game (loads all shaders/textures/levels/gameobjects/camera/etc)
        void update(float deltaTime);
        void render();
};

#endif