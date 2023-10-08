#pragma once

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <iostream>
#include <assert.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <glad/glad.h>

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

    public:
        //Loop flag
        bool quit = false;
        //Window handle
        SDL_Window* window = nullptr;
        //Opengl Context
        SDL_GLContext glContext;
        //Used to store and get events from SDL
        SDL_Event eventHandle;
        /* Used to store reference of the SDLjoystick
        * Must be used as referenced pointer and not a new pointer! 
        
        */
        SDL_GameController* joystick = nullptr;

        //delta time variable for updating input, physics, and kind of movement
        float DeltaTime;
        //variable that can be set through input
        APP_STATE App_State;
        INPUT_STATE Input_State;
        //variable storing window size
        unsigned int width, height;
        //Store known controller names
        const char* controllerNames[4];

        //constructor and also init shader, textures, etc...
        Window(int w, int h, const char* name);
        //destructor
        ~Window();
        //used to get SDL events and input checks
        void getEvents();
        //used as a forward of getEvents() to add additional input or event checks
        virtual void input(SDL_Event handle);

        virtual void init(); //used to call classes that handle the loading of shaders, textures, and objects
        
        virtual void update(); //used to update logic, custom events, and other
        
        virtual void render(); //used to render things on the screen
        //frame profiling
        void getFrameTime(float count);
};

#endif