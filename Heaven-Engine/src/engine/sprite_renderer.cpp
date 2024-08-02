#include <engine/sprite_renderer.hpp>

// Standard library
#include <iostream>

// initialize static variables
SpriteRenderer::RendererStats       SpriteRenderer::stats;
const glm::vec4                     SpriteRenderer::quadVertexPositions[4] = {
    {0.5f, 0.5f, 0.0f, 1.0f},
    {-0.5f, 0.5f, 0.0f, 1.0f},
    {0.5f, -0.5f, 0.0f, 1.0f},
    {-0.5f, -0.5f, 0.0f, 1.0f}};
// initialize buffer
SpriteRenderer::Vertex*             SpriteRenderer::quadBuffer = nullptr;
SpriteRenderer::Vertex*             SpriteRenderer::quadBufferPtr = nullptr;
// initialize graphics data
unsigned int                        SpriteRenderer::quadVAO;
unsigned int                        SpriteRenderer::quadVBO;
unsigned int                        SpriteRenderer::quadEBO;
unsigned int                        SpriteRenderer::indexCount;
// initialize changeable shader
Shader                              SpriteRenderer::shader;
// initialize "Universal" sprite size for all quads under this renderer
glm::uvec2                          SpriteRenderer::spriteSize;
// initialize auto clear var
bool                                SpriteRenderer::isAutoClearSet = false;

void SpriteRenderer::Init(Shader& s, glm::uvec2 sp){
    // set up automatic clear()
    setUpAutoClear();

    // set the shader reference
    shader = s;

    // set up shader samples for the quad textures
    shader.Use();
    
    // grab the uniform location of 'image' in the shader, the name 'image' is explicit
    auto loc = glGetUniformLocation(shader.ID, "image");

    // set up array to the size of the max number of textures
    int samplers[maxTextureSlots];

    // set up samplers array
    for (int i = 0; i < maxTextureSlots; i++)
    {
        samplers[i] = i;
    }

    // set up the index of the shader's texture array
    glUniform1iv(loc, maxTextureSlots, samplers);

    // set up sprite model view
    spriteSize = sp;

    // set up rendering of quads
    initRenderData(); 
}

void SpriteRenderer::Draw(int texIndex, glm::vec2 pos, glm::vec2 size, float rot, glm::vec4 color, const glm::vec4 vertexPositions[]){
    //? check if buffer hasn't been set up
    if(quadBuffer == nullptr){
        //! Display error
        std::cout << "ERROR: Missing render buffer initialization!\n";
        return; // stop function
    }

    // reset render stats
    resetStats();
    // init the buffer
    beginBatch();

    // create the quad to render
    createQuad(pos, size, rot, texIndex, color, vertexPositions);

    // render
    Flush();
}

void SpriteRenderer::Stack(int texIndex, glm::vec2 pos, glm::vec2 size, float rot, glm::vec4 color, const glm::vec4 vertexPositions[]){
    //? check if buffer hasn't been set up
    if(quadBuffer == nullptr){
        //! Display error
        std::cout << "ERROR: Missing render buffer initialization!\n";
        return; // stop function
    }

    // check if the buffer pointer hans't been set up
    if(quadBufferPtr == nullptr){
        // reset render stats
        resetStats();
        // then initialize the batch
        beginBatch();
    }

    // if not then add a quad to the buffer pointer

    // create the quad to render
    createQuad(pos, size, rot, texIndex, color, vertexPositions);
}

void SpriteRenderer::Flush(){
    //? check if buffer hasn't been set up
    if(quadBuffer == nullptr){
        //! Display error
        std::cout << "ERROR: Missing render buffer initialization!\n";
        return; // stop function
    }

    // set up vertex dynamic buffer
    if(!endBatch()){
        // there are no quads to render
        //! Display Warning
        std::cout << "WARNING: No quad added to draw!\n";
        return; // stop function
    }

    // draw the quad/s
    glBindVertexArray(quadVAO);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
    stats.drawCount++;

    // reset buffer pointer
    quadBufferPtr = nullptr;

    // reset index count
    indexCount = 0;
}

void SpriteRenderer::createQuad(glm::vec2& pos, glm::vec2 &size, float &rotation, int &texIndex, glm::vec4 &color, const glm::vec4 vertexPositions[]){
    // check if not over the index count
    if (indexCount >= maxIndexCount){
        // flush what's left and start another batch
        endBatch();
        Flush();  
        beginBatch();
    }

    // create model transform
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(pos, 0.0f)) 
    * glm::rotate(glm::mat4(1.0f), rotation, {0.0f, 0.0f, 1.0f}) 
    * glm::scale(glm::mat4(1.0f), {size.x, size.y, 0.0f});

    quadBufferPtr->position =
        (transform * vertexPositions[0]) *
        glm::scale(glm::mat4(1.0f),
                   glm::vec3(spriteSize.x, spriteSize.y, 1.0f));
    quadBufferPtr->texCoords = {0.0f, 0.0f};
    quadBufferPtr->texIndex = texIndex;
    quadBufferPtr->color = color;
    quadBufferPtr++;

    quadBufferPtr->position =
        (transform * vertexPositions[1]) *
        glm::scale(glm::mat4(1.0f),
                   glm::vec3(spriteSize.x, spriteSize.y, 1.0f));
    quadBufferPtr->texCoords = {-1.0f, 0.0f};
    quadBufferPtr->texIndex = texIndex;
    quadBufferPtr->color = color;
    quadBufferPtr++;

    quadBufferPtr->position =
        (transform * vertexPositions[2]) *
        glm::scale(glm::mat4(1.0f),
                   glm::vec3(spriteSize.x, spriteSize.y, 1.0f));
    quadBufferPtr->texCoords = {0.0f, 1.0f};
    quadBufferPtr->texIndex = texIndex;
    quadBufferPtr->color = color;
    quadBufferPtr++;

    quadBufferPtr->position =
        (transform * vertexPositions[3]) *
        glm::scale(glm::mat4(1.0f),
                   glm::vec3(spriteSize.x, spriteSize.y, 1.0f));
    quadBufferPtr->texCoords = {-1.0f, 1.0f};
    quadBufferPtr->texIndex = texIndex;
    quadBufferPtr->color = color;
    quadBufferPtr++;

    indexCount += 6;
    stats.quadCount++;
}

// Set up the quad rendering
void SpriteRenderer::initRenderData(){
    // check if quad buffer had already been initialize
    if (quadBuffer != nullptr)
        exit(-1); // avoid re-initalize the render data

    // configure buffer
    quadBuffer = new Vertex[maxVertexCount];

    // configure VAO/VBO/EBO
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);

    glBindVertexArray(quadVAO);

    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * maxVertexCount, nullptr, GL_DYNAMIC_DRAW);

    // vertex attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    // texture coordinates attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *)offsetof(Vertex, texCoords));
    glEnableVertexAttribArray(1);

    // texture index attribute
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *)offsetof(Vertex, texIndex));
    glEnableVertexAttribArray(2);

    // color attribute
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void *)offsetof(Vertex, color));
    glEnableVertexAttribArray(3);

    // indices buffer data
    unsigned int indices[maxIndexCount];
    unsigned int offset = 0;
    for (size_t i = 0; i < maxIndexCount; i += 6){
        indices[i + 0] = 0 + offset;
        indices[i + 1] = 1 + offset;
        indices[i + 2] = 2 + offset;

        indices[i + 3] = 2 + offset;
        indices[i + 4] = 3 + offset;
        indices[i + 5] = 1 + offset;

        offset += 4;
    }

    glGenBuffers(1, &quadEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void SpriteRenderer::beginBatch(){
    // set buffer pointer
    quadBufferPtr = quadBuffer;

    // call shader usage
    shader.Use();
}

bool SpriteRenderer::endBatch(){
    // calculate amount of quads to render
    GLsizeiptr size = (uint8_t *)quadBufferPtr - (uint8_t *)quadBuffer;
    if(size < 0){
        // no quads available
        return false;
    }
    
    // set up dynamic buffer
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, quadBuffer);

    // batch is fully set up
    return true;
}


const void SpriteRenderer::resetStats(){
    stats.quadCount = 0;
    stats.drawCount = 0;
}

void SpriteRenderer::clear(){
    // delete any pointers
    delete[] quadBuffer;
    quadBufferPtr = nullptr;
    delete quadBufferPtr;

    // delete quad buffer data
    glDeleteVertexArrays(1, &quadVAO);
    glDeleteBuffers(1, &quadVBO);
    glDeleteBuffers(1, &quadEBO);
}

void SpriteRenderer::setUpAutoClear(){
    // set up on exit to call the Clear()
    if(!isAutoClearSet && std::atexit(clear) == 0){
        isAutoClearSet = true; // disable calling this function again
    }
}