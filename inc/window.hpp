#pragma once

#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <unistd.h>
#include "../glad/glad.h"
#include <GLFW/glfw3.h>

//define window states
enum APP_STATE{
    ACTIVE, DEBUG
};

class Window{
    private:
        //vars used for frame profiling
        double prevTime = 0.0;
        double currentTime = 0.0;
        double timeDiff;
        unsigned int counter = 0;

    public:
        GLFWwindow* handle;
        //delta time variable for updating input, physics, and kind of movement
        float DeltaTime;
        //variable that can be set through input
        APP_STATE State;
        //variable storing window size
        unsigned int width, height;

        //constructor and also init shader, textures, etc...
        Window(int w, int h, const char* name);
        //destructor
        ~Window();
        //Primary window input
        void window_input();
        void init(); //used to call classes that handle the loading of shaders, textures, and objects
        void update();
        void render();
        //frame profiling
        void getFrameTime();
};

#endif