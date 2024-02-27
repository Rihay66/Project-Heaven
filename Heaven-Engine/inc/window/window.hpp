#pragma once

#ifndef WINDOW_HPP
#define WINDOW_HPP

// check platform
#ifdef __unix__ // Linux platform
    #include <unistd.h>
#elif defined(_WIN32) || defined(WIN32) // Windows platform
    #include <windows.h>
#endif

// GLFW and OPENGL Libraries
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// define window states
enum APP_STATE{
    ACTIVE, DEBUG
};

// define input state
enum INPUT_STATE{
    KM, KMANDCONTROLLER
};

class Window{
    private:
        // set up vars for calculating delta time and the fixed time step
	    double lastFrame = 0, currentFrame = 0, accumulator = 0, alpha = 0;

        // vars storing and reference to window size, width x height
        unsigned int width, height;

        /*Fixed rate that updates the stepUpdate(), adjust accordingly as needed
        * Default value is 0.16ms
        */
        double fixedTimeStep = 1.0f / 60.0f;

        // delta time variable for updating input, physics, and kind of movement
        double DeltaTime = 0;

        // window handle
        const GLFWwindow* handle;
    public:

        // state of the window application 
        APP_STATE App_State;
        // state of the window's input state
        INPUT_STATE Input_State;

        // constructor, initializes GLFW and OpenGL
        Window(int w, int h, const char* name);

        // destructor
        ~Window();

        // getters
        
        // used to grab the window handle context, without being able to modify the context directly
        GLFWwindow* getWindowHandle() {return (GLFWwindow*)this->handle;}

        // used to get Engine base input
        void getInput();

        /* returns the current deltatime, can be overwritten
            !Overwritting may need further modifications to the update() and stepUpdate() as it may cause unintended behavior
        */
        virtual float getDeltaTime();

        // returns the width of the window
        unsigned int getWidth(){return this->width;}
        
        // return the height of the window
        unsigned int getHeight(){return this->height;}

        // virtual functions

        /*Loops update(), stepUpdate(), and render()
        * Can be overwritten depending on the need of the game or application
        * NOTE: it is a single threaded function
        * !If overwritten, may need to apply calculations of fixed time step and accumulator yourself
        */
        virtual void runtime();

        // used as a forward of getInput() to add additional input or event checks
        virtual void input();

        // used to call classes that handle the loading of shaders, textures, and objects
        virtual void init(); 
        
        // used to update logic, custom events, and other
        virtual void update();

        // used to update Physics, ticks systems, or other at a fixed time step of 0.16ms
        virtual void stepUpdate(double ts);

        // used to render things on the screen 
        virtual void render(double alpha); 
};

#endif