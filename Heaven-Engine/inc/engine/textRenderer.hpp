#pragma once 

#ifndef TEXTRENDERING_HPP
#define TEXTRENDERING_HPP

#include <algorithm>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <resourceSys/shader.hpp>
#include <resourceSys/texture.hpp>

// Maximum texture width
#define MAXATLASWIDTH 1024

struct CharacterVertex{
    glm::vec2 position;
    glm::vec2 texCoords;
};

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

class TextRenderer{
    private:
        //Contain the texture id
        unsigned int textureID;

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

    public:

        //Shader used for text rendering
        Shader textShader;

        //Constructor       
        TextRenderer(unsigned int width, unsigned int height, const char* vShaderFile, const char* fShaderFile);
        //Destructor
        ~TextRenderer();
        
        //Create text quad
        void createTextQuad(const char* character, glm::vec2 pos, float scale, glm::vec4 color);

        //Load a font and sets a font size for the speicified font, returns false for error and returns true for success
        bool loadFont(const char* filename, unsigned int fontSize);
        //Draws text along with 
        void drawText(const char* text, glm::vec2 position, float scale, glm::vec4 color = glm::vec4(0.0f));
};

#endif