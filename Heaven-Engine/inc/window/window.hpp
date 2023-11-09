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
        //set up vars for calculating delta time
	    float lastFrame = 0, currentFrame = 0;

    public:
        //Window handle
        GLFWwindow* handle;
        //delta time variable for updating input, physics, and kind of movement
        float DeltaTime;
        //Returns the current deltatime
        virtual float getDeltaTime();

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

        //Used to run init() and loop update() and render()
        virtual void runtime();
        
        //Used to individually thread update() and render() 
        virtual void threadedRuntime();

        virtual void input();//used as a forward of getInput() to add additional input or event checks

        virtual void init(); //used to call classes that handle the loading of shaders, textures, and objects
        
        virtual void update(); //used to update logic, custom events, and other
        
        virtual void render(); //used to render things on the screen
};

#endif