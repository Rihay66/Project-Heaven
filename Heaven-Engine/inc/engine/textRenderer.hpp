#pragma once 

#ifndef TEXTRENDERING_HPP
#define TEXTRENDERING_HPP

#include <map>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <resourceSys/shader.hpp>
#include <resourceSys/texture.hpp>

class TextRenderer{
    private:
        //Store render states
        unsigned int VAO, VBO;

    public:
        //Constructor       
        TextRenderer(unsigned int width, unsigned int height);
        //Destructor
        ~TextRenderer();


};

#endif