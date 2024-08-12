#pragma once 

#ifndef TEXT_RENDERING_HPP
#define TEXT_RENDERING_HPP

#include <string>
#include <map>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <resourceSystems/managers/resource_manager.hpp>

/* A static singleton Text Renderer Class used to render text. This Class
uses a loaded font from the ResourceManager Class.
* NOTE: Text is rendered in the center of the screen
! This Class is unoptimized and not very flexible thus 
 take into consideration of its current design
*/
class TextRenderer{
    public:        
        // initialize the text renderer which requires the width and height of the display area and a loaded shader
        static void Init(unsigned int width, unsigned int height, Shader& shader);

        // Requires a font set from the ResourceManager, along with attributes of the text being displayed
        static void DisplayText(std::map<char, Character>& chars, std::string text, glm::vec2 position, glm::vec2 scale, glm::vec4 color = glm::vec4(1.0f));
    private:
        // stores data of a quad
        static unsigned int VAO, VBO;

        // initial setup of the rendering data
        static void initTextRenderingData();

        // shader used for text rendering
        static Shader textShader;

        // private constructor       
        TextRenderer() {}

        // used to clean up resources
        static void clear();

        //! Currently EXPERIMENTAL, may cause exceptions or segfaults
        // private boolean to track automatic clear()
        static bool isAutoClearSet;
        // set up automatic de-allocation of loaded resources
        static void setUpAutoClear();
};

#endif