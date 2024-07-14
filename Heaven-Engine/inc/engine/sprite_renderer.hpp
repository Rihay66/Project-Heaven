#pragma once

#ifndef RENDERER_HPP
#define RENDERER_HPP

// include standard lib
#include <vector>

// include math and glad
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// include shader and texture classes
#include <utilities/interpolation_utils.hpp>
#include <resourceSystems/shader.hpp>

//TODO: Rewrite the comments for clarity and proper format

/* A static singleton Sprite Rendering Class used to 
 render 2D quads. This class uses mainly the 
 GameObject Class to represent each quad. 
 This class utilizes batch rendering when
 rendering a LIST of GameObjects. 
!Requires a shader class and a standard sprite size 
*/
class SpriteRenderer{    
    public:
        // initialize the rendererm which requires a loaded shader and optionally changeable sprite size of all rendered objects
        static void Init(Shader& shader, glm::uvec2 spriteSize = {10.0f, 10.0f});

        //TODO: Allow for setting custom base quads corner positions

        // draw single a quad utilizing given raw data, without interpolation
        static void Draw(int texIndex, glm::vec2 pos, glm::vec2 size, float rotation, glm::vec4 color = glm::vec4(1.0f));

        /* store a single quad utilizing given raw data, without interpolation
            !Requires the Flush() in order to render what was stored
        */
        static void Stack(int texIndex, glm::vec2 pos, glm::vec2 size, float rotation, glm::vec4 color = glm::vec4(1.0f));
        
        // used to tell opengl to render the stored quads in the buffer
        static void Flush();

        // data struct for holding amount of draw calls and quad count
        struct RendererStats{
            int quadCount = 0, drawCount = 0;
        };

        // contain reference to amont of quads and amount of draw calls
        static RendererStats stats;
    private:

        // data struct of standard quad's vertex information
        struct Vertex{
            glm::vec2 position;
            glm::vec2 texCoords;
            float texIndex;
            glm::vec4 color;
        };


        // reference to the model size
        static glm::uvec2 spriteSize;

        // stores data of a passed in shader
        static Shader shader;

        // stores data of a quad
        static unsigned int quadVAO;
        static unsigned int quadVBO;
        static unsigned int quadEBO;

        // counter to track the number of vertices of quads
        static unsigned int indexCount;

        // stores max number of quads as a buffer
        static Vertex* quadBuffer;

        // stores the amount of wanted quad buffers
        static Vertex* quadBufferPtr;  

        // stores the amount of quads to render
        const static int maxQuadCount = 10000;
        const static int maxVertexCount = maxQuadCount * 4;
        const static int maxIndexCount = maxQuadCount * 6;

        // stores maximum amount of textures there can be
        const static int maxTextureSlots = 32;

        // used to store offsets of quad vertex positions
        const static glm::vec4 quadVertexPositions[];

        // private constructor 
        SpriteRenderer() {}

        // initial setup for rendering, setups the rendering of quads and their buffer data
        static void initRenderData();

        // used to draw a quad and to be stored in to the quad buffer 
        static void createQuad(glm::vec2 &size, float &rotation, int &texIndex, glm::vec4 &color, State &inter);

        // used to set the quad vertex buffers
        static void beginBatch();
        
        // used to calculate amount of quads to be rendered, returns false for there are no quads and true for there are quads available
        static bool endBatch();

        // resets stats such as draw calls and amount quads
        const static void resetStats();

        // used to clean up resources
        static void clear();

        //! Currently EXPERIMENTAL, may cause exceptions or segfaults
        // private boolean to track automatic clear()
        static bool isAutoClearSet;
        // set up automatic de-allocation of loaded resources
        static void setUpAutoClear();
};

#endif