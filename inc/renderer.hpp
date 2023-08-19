#pragma once

#ifndef RENDERER_H
#define RENDERER_H

//include standard lib
#include <vector>
#include <algorithm>

//include math and glad
#include "../glad/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//include shader and texture classes
#include "../inc/gameObject.hpp"
#include "../inc/shader.hpp"

//data struct for holding 2 vertex positions
struct vec2{
    float x, y;
};

//data struct for holding vertex info
struct Vertex{ 
    vec2 position;
    vec2 texCoords;
    float texIndex;
};

struct RendererStats{
    int quadCount = 0, drawCount = 0;
};

class Renderer{
    public:
        //constructor & desconstructor
        Renderer(Shader &shader, glm::vec2 spriteSize);
        ~Renderer();

        //draw multiple pointer objects in a vector list
        void Draw2D(std::vector<GameObject*> objs, glm::vec3 color = glm::vec3(1.0f));

        //reference to the model size
        glm::vec2 spriteSize;

        //contain reference to amont of quads and amount of draw calls
        RendererStats stats;

    private:
        //stores data of a passed in shader
        Shader shader;
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

        //initial setup for rendering, setups the rendering of quads and their buffer data
        void initRenderData();

        //Used to set the size of sprites
        void setSpriteSize();

        //used to draw a quad
        void createQuad(glm::vec2 pos, float size, float texIndex);

        //Used to set and unset the vertex buffers
        void beginBatch();
        void endBatch();

        //Used to tell opengl to render the triangles
        void flush();

        const void resetStats();
};

#endif