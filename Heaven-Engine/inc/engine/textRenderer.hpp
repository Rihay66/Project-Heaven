#pragma once 

#ifndef TEXTRENDERING_HPP
#define TEXTRENDERING_HPP

#include <algorithm>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <resourceSys/resourceManager.hpp>

//! THIS CLASS SHOULDN"T BE USED AS IT WILL BE REFACTORED AT A LATER DATA

// Maximum texture width
#define MAXATLASWIDTH 1024

struct CharacterVertex{
    glm::vec2 position;
    glm::vec2 texCoords;
};
//! THIS CLASS SHOULDN"T BE USED AS IT WILL BE REFACTORED AT A LATER DATA
struct Characters{
    float ax; // advance.x
    float ay; // advance.y

    float bw; // bitmap.width;
    float bh; // bitmap.height;

    float bl; // bitmap_left;
    float bt; // bitmap_top;

    float tx; // x offset of glyph in texture coordinates
    float ty; // y offset of glyph in texture coordinates
};
//! THIS CLASS SHOULDN"T BE USED AS IT WILL BE REFACTORED AT A LATER DATA
class TextRenderer{
    private:
        //Contain the texture id
        unsigned int textureID;

        //texture resulution
        unsigned int texW;
        unsigned int texH;

        //Create a array of 128 characters
        Characters c[128];

        //stores data of a quad
        unsigned int quadVAO;
        unsigned int quadVBO;

        //stores the quad buffer
        CharacterVertex* quadBuffer = nullptr;
        CharacterVertex* quadBufferPtr = nullptr;  

        //stores the ammount of triangles to render
        unsigned int vertexCount;

        const static int maxQuadCount = 10000;
        const static int maxVertexCount = maxQuadCount * 6;

        //initial setup of the rendering data
        void initTextRenderingData();

        //Used to set and unset the vertex buffers
        void beginBatch();
        void endBatch();

        //Used to tell opengl to render the triangles
        void flush();

        //Shader used for text rendering
        Shader textShader;
    public:
        //Constructor       
        TextRenderer(unsigned int width, unsigned int height, Shader& shader);
        //Destructor
        ~TextRenderer();
        
        //Create text quad
        void createTextQuad(const uint8_t* character, glm::vec2 pos, glm::vec2 scale, glm::vec4 color);
        
        //Draws text along with 
        void drawText(const char* text, glm::vec2 position, glm::vec2 scale, glm::vec4 color = glm::vec4(1.0f));
};

#endif