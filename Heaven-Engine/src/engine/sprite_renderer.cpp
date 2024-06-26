#include <engine/sprite_renderer.hpp>

const void SpriteRenderer::resetStats(){
    this->stats.quadCount = 0;
    this->stats.drawCount = 0;
}

SpriteRenderer::SpriteRenderer(Shader &shader, glm::uvec2 spriteSize){
    this->shader = shader;

    // set up shader samples for the quad textures
    this->shader.Use();
    
    // grab the uniform location of 'image' in the shader, the name 'iamge' is explicit
    auto loc = glGetUniformLocation(this->shader.ID, "image");

    // set up array to the size of the max number of textures
    int samplers[this->maxTextureSlots];

    // set up samplers array
    for (int i = 0; i < this->maxTextureSlots; i++)
    {
        samplers[i] = i;
    }

    // set up the index of the shader's texture array
    glUniform1iv(loc, maxTextureSlots, samplers);

    // set up shader model view
    this->spriteSize = spriteSize;

    // set up quad vertex positions
    quadVertexPositions[0] = {0.5f, 0.5f, 0.0f, 1.0f};
    quadVertexPositions[1] = {-0.5f, 0.5f, 0.0f, 1.0f};
    quadVertexPositions[2] = {0.5f, -0.5f, 0.0f, 1.0f};
    quadVertexPositions[3] = {-0.5f, -0.5f, 0.0f, 1.0f};

    // set up rendering of quads
    this->initRenderData(); 
}

SpriteRenderer::~SpriteRenderer(){
    // delete any pointers
    delete[] this->quadBuffer;
    this->quadBufferPtr = nullptr;
    delete this->quadBufferPtr;

    // delete quad buffer data
    glDeleteVertexArrays(1, &this->quadVAO);
    glDeleteBuffers(1, &this->quadVBO);
    glDeleteBuffers(1, &this->quadEBO);
}

void SpriteRenderer::createQuad(GameObject::RenderType &type, glm::vec2 &size, float rotation, int &texIndex, glm::vec4 &color, State &inter){

    // check if not over the index count
    if (this->indexCount >= this->maxIndexCount){
        // flush what's left and start another batch
        this->endBatch();
        this->flush();
        this->beginBatch();
    }

    // create model transform
    transform = glm::translate(glm::mat4(1.0f), glm::vec3(inter.posX, inter.posY, 0.0f)) 
    * glm::rotate(glm::mat4(1.0f), rotation, {0.0f, 0.0f, 1.0f}) 
    * glm::scale(glm::mat4(1.0f), {size.x, size.y, 0.0f});
    
    //TODO: Simplify the code below to be less lines of code
    
    // check GameObject rendering state
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

// render multiple objects pointers
void SpriteRenderer::Draw2D(std::vector<GameObject *> &gameObjects, double alpha){

    // init the buffer
    this->resetStats();
    this->beginBatch();

    // bind textures
    ResourceManager::BindTextures();

    // loop through objects and add to batch
    for (int i = 0; i < gameObjects.size(); i++)
    {
        // skip objects that are null or aren't set
        if(gameObjects[i] == nullptr)
            continue; // skip iteration

        if (gameObjects[i]->getInterpolationFlag())
        {
            interpolateState(this->interpolation, alpha, gameObjects[i]->getPreviousInterpolatedState(), gameObjects[i]->getCurrentInterpolatedState());
        }else{
            interpolation.posX = gameObjects[i]->position.x;
            interpolation.posY = gameObjects[i]->position.y;
        }

        this->createQuad(gameObjects[i]->renderType, gameObjects[i]->size, gameObjects[i]->getRotationRadians(), gameObjects[i]->textureIndex, gameObjects[i]->color, interpolation);
    }

    // Set dynamic vertex buffer
    this->endBatch();
    // draw
    this->flush();
}

// render multiple objects pointers
void SpriteRenderer::Draw2D(std::vector<GameObject> &gameObjects, double alpha){

    // init the buffer
    this->resetStats();
    this->beginBatch();

    // bind textures
    ResourceManager::BindTextures();

    // loop through objects and add to batch
    for (int i = 0; i < gameObjects.size(); i++)
    {
        if (gameObjects[i].getInterpolationFlag())
        {
            interpolateState(this->interpolation, alpha, gameObjects[i].getPreviousInterpolatedState(), gameObjects[i].getCurrentInterpolatedState());
        }else{
            interpolation.posX = gameObjects[i].position.x;
            interpolation.posY = gameObjects[i].position.y;
        }

        this->createQuad(gameObjects[i].renderType, gameObjects[i].size, gameObjects[i].getRotationRadians(), gameObjects[i].textureIndex, gameObjects[i].color, interpolation);
    }

    // set dynamic vertex buffer
    this->endBatch();
    // draw
    this->flush();
}

// render a single object pointer
void SpriteRenderer::Draw2D(GameObject *&obj, double alpha)
{
    // init the buffer
    this->resetStats();
    this->beginBatch();

    // bind textures
    ResourceManager::BindTextures();

    // skip object that is not set
    if(obj == nullptr){
        // finish buffer
        this->endBatch();
        // draw
        this->flush();
        return; // stop function
    }

    if (obj->getInterpolationFlag()){
        interpolateState(this->interpolation, alpha, obj->getPreviousInterpolatedState(), obj->getCurrentInterpolatedState());
    }else{
        interpolation.posX = obj->position.x;
        interpolation.posY = obj->position.y;
    }

    // add a single object to the batch
    this->createQuad(obj->renderType, obj->size, obj->getRotationRadians(), obj->textureIndex, obj->color, interpolation);

    // set dynamic vertex buffer
    this->endBatch();
    // draw
    this->flush();
}

// render a single object pointer
void SpriteRenderer::Draw2D(GameObject &obj, double alpha){

    // init the buffer
    this->resetStats();
    this->beginBatch();

    if (obj.getInterpolationFlag()){
        interpolateState(this->interpolation, alpha, obj.getPreviousInterpolatedState(), obj.getCurrentInterpolatedState());
    }else{
        interpolation.posX = obj.position.x;
        interpolation.posY = obj.position.y;
    }

    // add a single object to the batch
    this->createQuad(obj.renderType, obj.size, obj.getRotationRadians(), obj.textureIndex, obj.color, interpolation);

    // set dynamic vertex buffer
    this->endBatch();
    // draw
    this->flush();
}

// Set up the quad rendering
void SpriteRenderer::initRenderData(){

    // check if quad buffer had already been initialize
    if (this->quadBuffer != nullptr)
        exit(-1); // avoid re-initalize the render data

    // configure buffer
    this->quadBuffer = new Vertex[this->maxVertexCount];

    // configure VAO/VBO/EBO
    glGenVertexArrays(1, &this->quadVAO);
    glGenBuffers(1, &this->quadVBO);

    glBindVertexArray(this->quadVAO);

    glBindBuffer(GL_ARRAY_BUFFER, this->quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * this->maxVertexCount, nullptr, GL_DYNAMIC_DRAW);

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

    glGenBuffers(1, &this->quadEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->quadEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void SpriteRenderer::beginBatch(){
    // set buffer pointer
    this->quadBufferPtr = quadBuffer;

    // call shader usage
    this->shader.Use();
}

void SpriteRenderer::endBatch(){
    // calculate amount of quads to render
    GLsizeiptr size = (uint8_t *)this->quadBufferPtr - (uint8_t *)this->quadBuffer;
    // set up dynamic buffer
    glBindBuffer(GL_ARRAY_BUFFER, this->quadVBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, quadBuffer);
}

void SpriteRenderer::flush(){
    // draw the quad/s
    glBindVertexArray(this->quadVAO);
    glDrawElements(GL_TRIANGLES, this->indexCount, GL_UNSIGNED_INT, nullptr);
    this->stats.drawCount++;

    // reset index count
    this->indexCount = 0;
}