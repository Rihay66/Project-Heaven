#include <engine/renderer.hpp>

const void Renderer::resetStats(){
    this->stats.quadCount = 0;
    this->stats.drawCount = 0;
}

Renderer::Renderer(Shader &shader, glm::vec2 spriteSize){
    this->shader = shader;

    //set up shader samples for the quad textures
    this->shader.Use();

    auto loc = glGetUniformLocation(this->shader.ID, "image");
    
    int samplers[this->maxTextureSlots];

    //set up samplers array
    for(int i = 0; i < this->maxTextureSlots; i++){
        samplers[i] = i;
    }

    glUniform1iv(loc, maxTextureSlots, samplers);

    //set up shader model view
    this->spriteSize = spriteSize;

    //set up quad vertex positions
    quadVertexPositions[0] = {0.5f, 0.5f, 0.0f, 1.0f};
    quadVertexPositions[1] = {-0.5f, 0.5f, 0.0f, 1.0f};
    quadVertexPositions[2] = {0.5f, -0.5f, 0.0f, 1.0f};
    quadVertexPositions[3] = {-0.5f, -0.5f, 0.0f, 1.0f};

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

void Renderer::createQuad(GameObject::RenderType &type, glm::vec2 &pos, glm::vec2 &size, float &rotation, int &texIndex, glm::vec4 &color){

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

    switch (type){
        case GameObject::RenderType::Default:
            quadBufferPtr->position = (transform * quadVertexPositions[0]) * glm::scale(glm::mat4(1.0f), glm::vec3(spriteSize.x, spriteSize.y, 1.0f));
            quadBufferPtr->texCoords = {0.0f, 0.0f};
            quadBufferPtr->texIndex = texIndex;
            quadBufferPtr->color = color;
            quadBufferPtr++;

            quadBufferPtr->position = (transform * quadVertexPositions[1]) * glm::scale(glm::mat4(1.0f), glm::vec3(spriteSize.x, spriteSize.y, 1.0f));
            quadBufferPtr->texCoords = {-1.0f, 0.0f};
            quadBufferPtr->texIndex = texIndex;
            quadBufferPtr->color = color;
            quadBufferPtr++;

            quadBufferPtr->position = (transform * quadVertexPositions[2]) * glm::scale(glm::mat4(1.0f), glm::vec3(spriteSize.x, spriteSize.y, 1.0f));
            quadBufferPtr->texCoords = {0.0f, 1.0f};
            quadBufferPtr->texIndex = texIndex;
            quadBufferPtr->color = color;
            quadBufferPtr++;

            quadBufferPtr->position = (transform * quadVertexPositions[3]) * glm::scale(glm::mat4(1.0f), glm::vec3(spriteSize.x, spriteSize.y, 1.0f));
            quadBufferPtr->texCoords = {-1.0f, 1.0f};
            quadBufferPtr->texIndex = texIndex;
            quadBufferPtr->color = color;
            quadBufferPtr++;
            break;

        case GameObject::RenderType::flipVertically:
            quadBufferPtr->position = (transform * quadVertexPositions[0]) * glm::scale(glm::mat4(1.0f), glm::vec3(spriteSize.x, spriteSize.y, 1.0f));
            quadBufferPtr->texCoords = {0.0f, 0.0f};
            quadBufferPtr->texIndex = texIndex;
            quadBufferPtr->color = color;
            quadBufferPtr++;

            quadBufferPtr->position = (transform * quadVertexPositions[1]) * glm::scale(glm::mat4(1.0f), glm::vec3(spriteSize.x, spriteSize.y, 1.0f));
            quadBufferPtr->texCoords = {1.0f, 0.0f};
            quadBufferPtr->texIndex = texIndex;
            quadBufferPtr->color = color;
            quadBufferPtr++;

            quadBufferPtr->position = (transform * quadVertexPositions[2]) * glm::scale(glm::mat4(1.0f), glm::vec3(spriteSize.x, spriteSize.y, 1.0f));
            quadBufferPtr->texCoords = {0.0f, 1.0f};
            quadBufferPtr->texIndex = texIndex;
            quadBufferPtr->color = color;
            quadBufferPtr++;

            quadBufferPtr->position = (transform * quadVertexPositions[3]) * glm::scale(glm::mat4(1.0f), glm::vec3(spriteSize.x, spriteSize.y, 1.0f));
            quadBufferPtr->texCoords = {1.0f, 1.0f};
            quadBufferPtr->texIndex = texIndex;
            quadBufferPtr->color = color;
            quadBufferPtr++;
            break;

        case GameObject::RenderType::flipHorizontal:
            quadBufferPtr->position = (transform * quadVertexPositions[0]) * glm::scale(glm::mat4(1.0f), glm::vec3(spriteSize.x, spriteSize.y, 1.0f));
            quadBufferPtr->texCoords = {0.0f, 0.0f};
            quadBufferPtr->texIndex = texIndex;
            quadBufferPtr->color = color;
            quadBufferPtr++;

            quadBufferPtr->position = (transform * quadVertexPositions[1]) * glm::scale(glm::mat4(1.0f), glm::vec3(spriteSize.x, spriteSize.y, 1.0f));
            quadBufferPtr->texCoords = {-1.0f, 0.0f};
            quadBufferPtr->texIndex = texIndex;
            quadBufferPtr->color = color;
            quadBufferPtr++;

            quadBufferPtr->position = (transform * quadVertexPositions[2]) * glm::scale(glm::mat4(1.0f), glm::vec3(spriteSize.x, spriteSize.y, 1.0f));
            quadBufferPtr->texCoords = {0.0f, -1.0f};
            quadBufferPtr->texIndex = texIndex;
            quadBufferPtr->color = color;
            quadBufferPtr++;

            quadBufferPtr->position = (transform * quadVertexPositions[3]) * glm::scale(glm::mat4(1.0f), glm::vec3(spriteSize.x, spriteSize.y, 1.0f));
            quadBufferPtr->texCoords = {-1.0f, -1.0f};
            quadBufferPtr->texIndex = texIndex;
            quadBufferPtr->color = color;
            quadBufferPtr++;
            break;
        case GameObject::RenderType::flipBoth:
            quadBufferPtr->position = (transform * quadVertexPositions[0]) * glm::scale(glm::mat4(1.0f), glm::vec3(spriteSize.x, spriteSize.y, 1.0f));
            quadBufferPtr->texCoords = {0.0f, 0.0f};
            quadBufferPtr->texIndex = texIndex;
            quadBufferPtr->color = color;
            quadBufferPtr++;

            quadBufferPtr->position = (transform * quadVertexPositions[1]) * glm::scale(glm::mat4(1.0f), glm::vec3(spriteSize.x, spriteSize.y, 1.0f));
            quadBufferPtr->texCoords = {1.0f, 0.0f};
            quadBufferPtr->texIndex = texIndex;
            quadBufferPtr->color = color;
            quadBufferPtr++;

            quadBufferPtr->position = (transform * quadVertexPositions[2]) * glm::scale(glm::mat4(1.0f), glm::vec3(spriteSize.x, spriteSize.y, 1.0f));
            quadBufferPtr->texCoords = {0.0f, -1.0f};
            quadBufferPtr->texIndex = texIndex;
            quadBufferPtr->color = color;
            quadBufferPtr++;

            quadBufferPtr->position = (transform * quadVertexPositions[3]) * glm::scale(glm::mat4(1.0f), glm::vec3(spriteSize.x, spriteSize.y, 1.0f));
            quadBufferPtr->texCoords = {1.0f, -1.0f};
            quadBufferPtr->texIndex = texIndex;
            quadBufferPtr->color = color;
            quadBufferPtr++;
            break;
            
        default:
            break;
    }

    this->indexCount += 6;
    this->stats.quadCount++;
}

//render multiple objects pointers
void Renderer::Draw2D(std::vector<GameObject*> gameObjects){

    //init the buffer
    this->resetStats();
    this->beginBatch();

    //bind textures
    ResourceManager::BindTextures();

    //Loop through objects and add to batch
    for(int i = 0 ; i < gameObjects.size(); i++){
        this->createQuad(gameObjects[i]->renderType, gameObjects[i]->position, gameObjects[i]->size, gameObjects[i]->rotation, gameObjects[i]->textureIndex, gameObjects[i]->color);
    }

    //Set dynamic vertex buffer
    this->endBatch();
    //draw
    this->flush();
}

//render multiple objects pointers
void Renderer::Draw2D(std::vector<GameObject> &gameObjects){

    //init the buffer
    this->resetStats();
    this->beginBatch();

    //bind textures
    ResourceManager::BindTextures();

    //Loop through objects and add to batch
    for(int i = 0 ; i < gameObjects.size(); i++){
        this->createQuad(gameObjects[i].renderType, gameObjects[i].position, gameObjects[i].size, gameObjects[i].rotation, gameObjects[i].textureIndex, gameObjects[i].color);
    }

    //Set dynamic vertex buffer
    this->endBatch();
    //draw
    this->flush();
}

//render a single object pointer
void Renderer::Draw2D(GameObject* obj){

    //init the buffer
    this->resetStats();
    this->beginBatch();

    //Bind textures
    ResourceManager::BindTextures();

    //add a single object to the batch
    this->createQuad(obj->renderType, obj->position, obj->size, obj->rotation, obj->textureIndex, obj->color);

    //Set dynamic vertex buffer
    this->endBatch();
    //draw
    this->flush();
} 

//render a single object pointer
void Renderer::Draw2D(GameObject &obj){

    //init the buffer
    this->resetStats();
    this->beginBatch();

    //Bind textures
    ResourceManager::BindTextures();

    //add a single object to the batch
    this->createQuad(obj.renderType, obj.position, obj.size, obj.rotation, obj.textureIndex, obj.color);

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
    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, color));

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
    //Set buffer pointer
    this->quadBufferPtr = quadBuffer;

    //Call shader usage
    this->shader.Use();
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