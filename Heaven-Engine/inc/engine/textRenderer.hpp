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

// Hold character information which contains relative information from a character
struct Vertex {
    glm::vec2 position;
    glm::vec2 texCoords;
    float texIndex;
};

class TextRenderer{
    private:
       //stores data of a quad
        unsigned int quadVAO;
        unsigned int quadVBO;
        unsigned int quadEBO;

        //stores the quad buffer
        Vertex* quadBuffer = nullptr;
        Vertex* quadBufferPtr = nullptr;  

        //stores the ammount of triangles to render
        unsigned int indexCount;

        const static int maxQuadCount = 10000;
        const static int maxVertexCount = maxQuadCount * 4;
        const static int maxIndexCount = maxQuadCount * 6;

        //initial setup of the rendering data
        void initTextRenderingData();

    public:
        //Hold a map of pre-compiled characters
        std::map<char, Character> Characters;

        //Shader used for text rendering
        Shader textShader;

        //Constructor       
        TextRenderer(unsigned int width, unsigned int height, const char* vShaderFile, const char* fShaderFile);
        //Destructor
        ~TextRenderer();

        void loadFont(std::string filename, unsigned int fontSize);
        


};

#endif