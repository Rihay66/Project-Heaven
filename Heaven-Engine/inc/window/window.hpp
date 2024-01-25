#pragma once

#ifndef WINDOW_HPP
#define WINDOW_HPP

//Check platform
#ifdef __unix__ //Linux platform
    #include <unistd.h>
#elif defined(_WIN32) || defined(WIN32) //WIndows platform
    #include <windows.h>
#endif

//GLFW and OPENGL Libraries
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window{
    private:
        //set up vars for calculating delta time and the fixed time step
	    double lastFrame = 0, currentFrame = 0, accumulator = 0, alpha = 0;

    public:
        //define window states
        enum APP_STATE{
            ACTIVE, DEBUG
        };

        //define input state
        enum INPUT_STATE{
            KM, KMANDCONTROLLER
        };

        //Window handle
        GLFWwindow* handle;

        /*Fixed rate that updates the stepUpdate(), adjust accordingly as needed
        * Default value is 0.016 or 16ms
        */
        double fixedTimeStep = 1.0f / 60.0f;

        //delta time variable for updating input, physics, and kind of movement
        double DeltaTime = 0;

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

        //Returns the current deltatime
        virtual float getDeltaTime();

        /*Loop update() and render()
        * Can be overwritten dependin on the need of the game or application
        */
        virtual void runtime();

        //used as a forward of getInput() to add additional input or event checks
        virtual void input();

        //used to call classes that handle the loading of shaders, textures, and objects
        virtual void init(); 
        
        //used to update logic, custom events, and other
        virtual void update();

        //used to update Physics, ticks systems, or other
        virtual void stepUpdate(double ts);

        //used to render things on the screen
        virtual void render(double alpha); 
};

#endif