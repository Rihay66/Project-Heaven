#pragma once

#ifndef WINDOW_HPP
#define WINDOW_HPP

// check platform
#if defined(_WIN32) || defined(WIN32) // Windows platform
    #include <windows.h>
#endif

// GLFW and OPENGL libraries
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//TODO: Give more information about the class 

/* Window class used for creating a graphical window
 that is used to hold all that makes up an application.
 The window class provides various functions and most 
 functions are overwrittable. 
 !It is recommended to inherit this class
*/
class Window{
    private:
        // set up vars for calculating delta time and the fixed time step
	      double lastFrame = 0, currentFrame = 0, frameDuration = 0, accumulator = 0, 
          alpha = 0, threadSleepTime = 0;

        // vars storing and referencing to window size, width x height
        unsigned int width, height;

        // var storing and referencing to the window name
        const char* windowName;

        /*Fixed rate that updates the stepUpdate(), adjust accordingly as needed
         !Default value is 0.16ms
        */
        double fixedTimeStep = 1.0f / 60.0f;

        /*Fixed rate that updates application, adjust accordingly as needed
         !Default value is 0.16ms
        */
        double targetTimeStep = 1.0f / 60.0f;

        // delta time variable for updating input, physics, and kind of movement
        double DeltaTime = 0;

        // window handle
        GLFWwindow* handle = nullptr;

    protected:
        // used to set the target frame time between frame, aka max frame time
        void setTargetTimeStep(double time);
        // used to set the fixed frame time between frame
        void setFixedTimeStep(double time);
        // used to get windows's base input and calls input()
        void getInput();

    public:
        // constructor, in
        Window(int w, int h, const char* name = "");

        // destructor
        ~Window();

        //* Initialization functions

        /* used to initialize the window and it's contexts by default 
          initializes GLFW and creates a Window with OpenGL 4.5 capabilities
          !Overwritting is not recommended, however due note that runtime(), getDeltaTime(), 
          !getInput(), setUpOpenGL() require GLFW to be initialized and have a created context
        */ 
        virtual void initializeWindow();

        //* Getters functions
        
        // used to grab the window handle context, without being able to modify the context directly
        GLFWwindow* getWindowHandle() {return this->handle;}

        /* returns the current deltatime, can be overwritten
          !Overwritting may need further modifications to the update() and stepUpdate() as it may cause unintended behavior
        */
        virtual float getDeltaTime();

        // returns the width of the window
        unsigned int getWidth(){return this->width;}
        
        // return the height of the window
        unsigned int getHeight(){return this->height;}

        //* Virtual functions

        // used for adding additional glfw window hints 
        virtual void additionalWindowOptions();

        /* used for setting up OpenGL rendering
         !Default is 2D rendering
        */
        virtual void setUpOpenGL();

        /* Calls init() once, and then loops input(), getDeltaTime(), update(), stepUpdate(), and render()
          Can be overwritten depending on the need of the game or application
         *NOTE: it is a single threaded function
         *NOTE: calls GLFW poll events, swap buffers and clears the OpenGL color buffer
         !If overwritten, may need to apply calculations of time step, fixed time step and accumulator yourself
        */
        virtual void runtime();

        // used as a forward of getInput() to add additional input or event checks
        virtual void input();

        // used to call classes that handle the loading of shaders, textures, and objects
        virtual void init(); 
        
        // used to update logic, custom events, and other
        virtual void update();

        // used to update Physics, ticks systems, or other at a fixed time step
        virtual void stepUpdate(double ts);

        // used to render things on the screen 
        virtual void render(double alpha); 
};

#endif