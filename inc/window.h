#pragma once

#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <unistd.h>
#include "../glad/glad.h"
#include <GLFW/glfw3.h>

class Window{
    public:
        GLFWwindow* handle;
        //constructor and also init shader, textures, etc...
        Window(int w, int h, const char* name);
        //destructor
        ~Window();
        //Primary window input
        void window_input();
        void update();
        void render();
};

#endif