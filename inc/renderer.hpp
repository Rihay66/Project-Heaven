#pragma once

#ifndef RENDERER_H
#define RENDERER_H

//include standard lib
#include <vector>
#include <algorithm>
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
        Renderer(Shader &shader, glm::vec2 spriteSize);
        ~Renderer();

        //draw multiple pointer objects in a vector list
        void Draw2D(std::vector<GameObject*> objs, glm::vec3 color = glm::vec3(1.0f));
        //draw a singular pointer object
        void Draw2D(GameObject* obj, glm::vec3 color = glm::vec3(1.0f));

        //reference to the model size
        glm::vec2 spriteSize;

    private:
        Shader shader;
        //stores data of a quad
        unsigned int quadVAO;
        unsigned int quadVBO;
        unsigned int quadEBO;

        //stores the ammount of triangles to render
        unsigned int indexCount;
        int textureIndex;
        int lastKnownTextureUnit;

        const static int maxQuadCount = 10000;
        const static int maxVertexCount = maxQuadCount * 4;
        const static int maxIndexCount = maxQuadCount * 6;

        std::array<Vertex, maxQuadCount> vertices;

        //initial setup for rendering, setups the rendering of quads and their buffer data
        void initRenderData();

        //Used to set the size of sprites
        void setSpriteSize();
};

#endif