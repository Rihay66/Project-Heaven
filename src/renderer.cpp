#include "../inc/renderer.hpp"

const void Renderer::resetStats(){
    this->stats.quadCount = 0;
    this->stats.drawCount = 0;
}

Renderer::Renderer(Shader &shader, glm::vec2 spriteSize){
    this->shader = shader;

    //set up shader samples
    this->shader.Use();

    auto loc = glGetUniformLocation(this->shader.ID, "image");
    
    int samplers[32];

    //set up samplers array
    for(int i = 0; i < 32; i++){
        samplers[i] = i;
    }

    glUniform1iv(loc, 32, samplers);

    //set up shader model view
    this->spriteSize = spriteSize;

    //set up quad vertex positions
    quadVertexPositions[0] = {1.0f, 1.0f, 0.0f, 1.0f};
    quadVertexPositions[1] = {0.0f, 1.0f, 0.0f, 1.0f};
    quadVertexPositions[2] = {1.0f, 0.0f, 0.0f, 1.0f};
    quadVertexPositions[3] = {0.0f, 0.0f, 0.0f, 1.0f};

    this->initRenderData(); //set up rendering of quads
}

Renderer::~Renderer(){
    //delete quad buffer data 
    glDeleteVertexArrays(1, &this->quadVAO);
    glDeleteBuffers(1, &this->quadVBO);
    glDeleteBuffers(1, &this->quadEBO);

    //delete any pointers
    delete[] this->quadBuffer;
    this->quadBufferPtr = nullptr;
    delete this->quadBufferPtr;
}

void Renderer::createQuad(glm::vec2 pos, glm::vec2 size, float rotation, float texIndex, glm::vec3 color){

    //check if not over the index count
    if(this->indexCount >= this->maxIndexCount){
        this->endBatch();
        this->flush();
        this->beginBatch();
    }

    //create model transform
    glm::mat4 transform  = glm::translate(glm::mat4(1.0f), glm::vec3(pos.x, pos.y, 0.0f))
    * glm::rotate(glm::mat4(1.0f), rotation, {0.0f, 0.0f, 1.0f})
    * glm::scale(glm::mat4(1.0f), {size.x, size.y, 0.0f});

    quadBufferPtr->position = (transform * quadVertexPositions[0]) * glm::scale(glm::mat4(1.0f), glm::vec3(spriteSize.x, spriteSize.y, 1.0f));
    quadBufferPtr->texCoords = {0.0f, 0.0f};
    quadBufferPtr->texIndex = texIndex;
    quadBufferPtr->color = {color.x, color.y, color.z};
    quadBufferPtr++;

    quadBufferPtr->position =  (transform * quadVertexPositions[1]) * glm::scale(glm::mat4(1.0f), glm::vec3(spriteSize.x, spriteSize.y, 1.0f));
    quadBufferPtr->texCoords = {1.0f, 0.0f};
    quadBufferPtr->texIndex = texIndex;
    quadBufferPtr->color = {color.x, color.y, color.z};
    quadBufferPtr++;

    quadBufferPtr->position = (transform * quadVertexPositions[2]) * glm::scale(glm::mat4(1.0f), glm::vec3(spriteSize.x, spriteSize.y, 1.0f));
    quadBufferPtr->texCoords = {0.0f, 1.0f};
    quadBufferPtr->texIndex = texIndex;
    quadBufferPtr->color = {color.x, color.y, color.z};
    quadBufferPtr++;
    
    quadBufferPtr->position = (transform * quadVertexPositions[3]) * glm::scale(glm::mat4(1.0f), glm::vec3(spriteSize.x, spriteSize.y, 1.0f));
    quadBufferPtr->texCoords = {1.0f, 1.0f};
    quadBufferPtr->texIndex = texIndex;
    quadBufferPtr->color = {color.x, color.y, color.z};
    quadBufferPtr++;

    this->indexCount += 6;
    this->stats.quadCount++;
}

//render multiple objects pointers
void Renderer::Draw2D(std::vector<GameObject*> gameObjects){

    //init the buffer
    this->resetStats();
    this->beginBatch();

    //gen tex by cheking objs tex id
    for(int i = 0 ; i < gameObjects.size(); i++){
        createQuad(gameObjects[i]->position, gameObjects[i]->size, gameObjects[i]->rotation, gameObjects[i]->textureIndex, gameObjects[i]->color);
    }

    //Set dynamic vertex buffer
    this->endBatch();
    //draw
    this->flush();
}

//Set up the quad rendering
void Renderer::initRenderData(){

    // configure buffer
    if(this->quadBuffer != nullptr)
        exit(-1);

    this->quadBuffer = new Vertex[this->maxVertexCount];

    // configure VAO/VBO/EBO
    glCreateVertexArrays(1, &this->quadVAO);
    glCreateBuffers(1, &this->quadVBO);

    glBindVertexArray(this->quadVAO);

    glBindBuffer(GL_ARRAY_BUFFER, this->quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * this->maxVertexCount, nullptr, GL_DYNAMIC_DRAW);

    //vertex attribute
    glEnableVertexArrayAttrib(this->quadVBO, 0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, position));
    
    //texture coordinates attribute
    glEnableVertexArrayAttrib(this->quadVBO, 1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, texCoords));

    //texture index attribute
    glEnableVertexArrayAttrib(this->quadVBO, 2);
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, texIndex));

    //color attribute
    glEnableVertexArrayAttrib(this->quadVBO, 3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, color));

    //indices buffer data
    unsigned int indices[maxIndexCount];
    unsigned int offset = 0;
    for(size_t i = 0; i < maxIndexCount; i += 6){
        
        indices[i + 0] = 0 + offset;
        indices[i + 1] = 1 + offset;
        indices[i + 2] = 2 + offset;

        indices[i + 3] = 2 + offset;
        indices[i + 4] = 3 + offset;
        indices[i + 5] = 1 + offset;

        offset += 4;
    }

    glCreateBuffers(1, &this->quadEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->quadEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void Renderer::beginBatch(){
    this->quadBufferPtr = quadBuffer;
}

void Renderer::endBatch(){
    GLsizeiptr size = (uint8_t*)this->quadBufferPtr - (uint8_t*)this->quadBuffer;
    //set up dynamic buffer
    glBindBuffer(GL_ARRAY_BUFFER, this->quadVBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, quadBuffer);
}

void Renderer::flush(){
    glBindVertexArray(this->quadVAO);
    glDrawElements(GL_TRIANGLES, this->indexCount, GL_UNSIGNED_INT, nullptr);
    this->stats.drawCount++;

    //reset index count 
    this->indexCount = 0;
}