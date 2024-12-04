#pragma once

#ifndef SDL_WINDOW_HPP
#define SDL_WINDOW_HPP

// check platform
#if defined(_WIN32) || defined(WIN32) // Windows platform
    #include <windows.h>
#endif

// GLAD and SDL libraries
#include <glad/glad.h>

/* Window abstract class used for creating a graphical context
 window that is used to allow for OpenGL capabilities.
 The window class provides various functions and most
 functions are overwritable.
 !It is recommended to inherit this class and override functions
*/
class Window{
    private:
    
    protected:
    
    public:
        // constructor
        Window();

        // deconstructor
        ~Window();
};

#endif