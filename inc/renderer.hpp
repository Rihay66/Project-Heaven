#pragma once

#ifndef RENDERER_H
#define RENDERER_H

//testing in making quads
#include <array>

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

class Renderer{
    public:
        //constructor & desconstructor
        Renderer(Shader &shader);
        ~Renderer();

        void Draw2D(GameObject* obj1, GameObject* obj2, glm::vec2 spriteSize, glm::vec3 color = glm::vec3(1.0f));
    
    private:
        Shader shader;
        //stores data of a quad
        unsigned int quadVAO;
        unsigned int quadVBO;
        unsigned int quadEBO;

        const size_t maxQuadCount = 10000;
        const size_t maxVertexCount = maxQuadCount * 4;
        const size_t maxIndexCount = maxQuadCount * 6;

        //initial setup for rendering, setups the rendering of quads and their buffer data
        void initRenderData();

        //Used to set the size of sprites
        void setSpriteSize(glm::vec2 spriteSize);
};

#endif