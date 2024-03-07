#pragma once

#ifndef RENDERER_HPP
#define RENDERER_HPP

// include standard lib
#include <vector>
#include <algorithm>

// include math and glad
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// include shader and texture classes
#include <gameObjects/game_object.hpp>
#include <resourceSystems/resource_manager.hpp>

/*
Rendering Class used to render *ONLY* type GameObjects and/or it's child classses
!Requires a shader class and a standard sprite size 
*/
class Renderer{
    public:
        // constructor & desconstructor
        Renderer(Shader &shader, glm::uvec2 &spriteSize);
        ~Renderer();

        // draw multiple pointer objects in a vector list, objects become batch rendered
        void Draw2D(std::vector<GameObject*> &objs, double &alpha);

        // draw multiple non-pointer objects in a vector list, objects become batch rendered
        void Draw2D(std::vector<GameObject> &objs, double &alpha);

        // draw a single pointer object
        void Draw2D(GameObject* &obj, double &alpha);

        // draw a single non-pointer object
        void Draw2D(GameObject &obj, double &alpha);

        // data struct for holding amount of draw calls and quad count
        struct RendererStats{
            int quadCount = 0, drawCount = 0;
        };

        // contain reference to amont of quads and amount of draw calls
        RendererStats stats;
        
    private:
        // reference to the model size
        glm::uvec2 spriteSize;

        // stores data of a passed in shader
        Shader shader;

        // stores data of a quad

        unsigned int quadVAO;
        unsigned int quadVBO;
        unsigned int quadEBO;

        // data struct of standard quad's vertex information
        struct Vertex{
            glm::vec2 position;
            glm::vec2 texCoords;
            float texIndex;
            glm::vec4 color;
        };

        // stores max number of quads as a buffer
        Vertex* quadBuffer = nullptr;

        // stores the amount of wanted quad buffers
        Vertex* quadBufferPtr = nullptr;  

        // counter to track the number of vertices of quads
        unsigned int indexCount;

        // stores the amount of quads to render
        const static int maxQuadCount = 10000;
        const static int maxVertexCount = maxQuadCount * 4;
        const static int maxIndexCount = maxQuadCount * 6;

        // stores maximum amount of textures there can be
        const static int maxTextureSlots = 32;

        // used to store offsets of quad vertex positions
        glm::vec4 quadVertexPositions[4];

        // a overwrittable State struct, used in linear interpolation
        State interpolation;

        // a overwrittable transform matrix
        glm::mat4 transform;

        // initial setup for rendering, setups the rendering of quads and their buffer data
        void initRenderData();

        // used to draw a quad and to be stored in to the quad buffer 
        void createQuad(GameObject::RenderType &type, glm::vec2 &pos, glm::vec2 &size, 
        float &rotation, int &texIndex, glm::vec4 &color, State &inter);

        // used to set the quad vertex buffers
        void beginBatch();
        
        // used to calculate amount of quads to be rendered
        void endBatch();

        // used to tell opengl to render the triangles
        void flush();

        // resets stats such as draw calls and amount quads
        const void resetStats();
};

#endif