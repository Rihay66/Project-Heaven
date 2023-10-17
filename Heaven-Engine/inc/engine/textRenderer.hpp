#pragma once 

#ifndef TEXTRENDERING_HPP
#define TEXTRENDERING_HPP

#include <map>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <resourceSys/shader.hpp>
#include <resourceSys/texture.hpp>

// Holds all state information relevant to a character as loaded using FreeType
struct Character {
    unsigned int TextureID; // ID handle of the glyph texture
    glm::ivec2   Size;      // size of glyph
    glm::ivec2   Bearing;   // offset from baseline to left/top of glyph
    unsigned int Advance;   // horizontal offset to advance to next glyph
};

class TextRenderer{
    private:
        //Store render states
        unsigned int VAO, VBO;

    public:
        //Hold a map of pre-compiled characters
        std::map<char, Character> Characters;

        //Shader used for text rendering
        Shader textShader;

        //Constructor       
        TextRenderer(unsigned int width, unsigned int height);
        //Destructor
        ~TextRenderer();

        void loadFont(std::string filename, unsigned int fontSize);
        


};

#endif