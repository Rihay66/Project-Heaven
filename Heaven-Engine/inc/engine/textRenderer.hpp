#pragma once 

#ifndef TEXTRENDERING_HPP
#define TEXTRENDERING_HPP

#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <resourceSys/resourceManager.hpp>

class TextRenderer{
    private:
        //stores data of a quad
        unsigned int VAO;
        unsigned int VBO;

        //initial setup of the rendering data
        void initTextRenderingData();

        //Shader used for text rendering
        Shader textShader;
    public:
        //Constructor       
        TextRenderer(unsigned int width, unsigned int height, Shader& shader);
        //Destructor
        ~TextRenderer();
        
        //Draws text along with 
        void drawText(std::string text, glm::vec2 position, glm::vec2 scale, glm::vec4 color = glm::vec4(1.0f));
};

#endif