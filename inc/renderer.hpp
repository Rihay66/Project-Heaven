#pragma once

#ifndef RENDERER_H
#define RENDERER_H

//include math and glad
#include "../glad/glad.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//include shader and texture classes
#include "../inc/texture.hpp"
#include "../inc/shader.hpp"

class Renderer{
    public:
        //constructor & desconstructor
        Renderer(Shader &shader);
        ~Renderer();

        void Draw2D(Texture2D &texture, glm::vec2 position, glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotation = 0.0f, glm::vec3 color = glm::vec3(1.0f));
    
    private:
        Shader shader;
        //stores data of a quad
        unsigned int quadVAO;
        unsigned int quadVBO;
        unsigned int quadEBO;

        //initial setup for rendering, setups the rendering of quads and their buffer data
        void initRenderData();
};

#endif