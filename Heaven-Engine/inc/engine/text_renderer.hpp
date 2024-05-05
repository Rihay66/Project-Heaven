#pragma once 

#ifndef TEXT_RENDERING_HPP
#define TEXT_RENDERING_HPP

#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <resourceSystems/shader.hpp>

/* Text Renderer Class used to render text. This Class
uses only one loaded font from the ResourceManager Class.
* NOTE: Text is rendered in the center of the screen
! This Class is unoptimized and not very flexible thus 
 take into consideration of its current design
*/
class TextRenderer{
    private:
        // stores data of a quad
        unsigned int VAO;
        unsigned int VBO;

        // initial setup of the rendering data
        void initTextRenderingData();

        // shader used for text rendering
        Shader textShader;
    public:
        // constructor       
        TextRenderer(unsigned int width, unsigned int height, Shader& shader);
        // destructor
        ~TextRenderer();
        
        // draws text along with with their position, scale, and color 
        void drawText(std::string text, glm::vec2 position, glm::vec2 scale, glm::vec4 color = glm::vec4(1.0f));
};

#endif