#pragma once

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <iostream>
//Check platform
#ifdef __unix__ //Linux platform
    #include <unistd.h>
#elif defined(_WIN32) || defined(WIN32) //WIndows platform
    #include <windows.h>
#endif

//Threading library
#include <thread>

//GLFW and OPENGL Libraries
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//define window states
enum APP_STATE{
    ACTIVE, DEBUG
};

//define input state
enum INPUT_STATE{
    KM, KMANDCONTROLLER
};

class Window{
    private:
        //vars used for frame profiling
        double prevTime = 0.0;
        double currentTime = 0.0;
        double timeDiff;
        unsigned int counter = 0;

        //set up vars for calculating delta time
	    float deltaTime = 0, lastFrame = 0, currentFrame = 0;

    public:
        //Window handle
        GLFWwindow* handle;
        //delta time variable for updating input, physics, and kind of movement
        float DeltaTime;
        //variable that can be set through input
        APP_STATE App_State;
        INPUT_STATE Input_State;
        //variable storing window size
        unsigned int width, height;

        //constructor and also init shader, textures, etc...
        Window(int w, int h, const char* name);
        //destructor
        ~Window();
        //used to get Engine base input
        void getInput();
        
        //Used to individually thread update() and render() 
        void threadedRuntime();

        virtual void input();//used as a forward of getInput() to add additional input or event checks

        virtual void init(); //used to call classes that handle the loading of shaders, textures, and objects
        
        virtual void update(); //used to update logic, custom events, and other
        
        virtual void render(); //used to render things on the screen
};

#endif