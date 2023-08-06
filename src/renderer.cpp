#include "../inc/renderer.hpp"

Renderer::Renderer(Shader &shader){
    this->shader = shader;
    this->initRenderData(); //set up rendering of quads
}

Renderer::~Renderer(){
    //delete quad buffer data 
    glDeleteVertexArrays(1, &this->quadVAO);
    glDeleteBuffers(1, &this->quadVBO);
    glDeleteBuffers(1, &this->quadEBO);
}

static std::array<Vertex, 4> createQuad(float x, float y, float texIndex){
    
    float size = 1.0f;
    
    Vertex v0;
    v0.position = {x + size, y + size};
    v0.texCoords = {1.0f, 1.0f};
    v0.texIndex = texIndex;

    Vertex v1;
    v1.position = {x, y + size};
    v1.texCoords = {0.0f, 1.0f};
    v1.texIndex = texIndex;

    Vertex v2;
    v2.position = {x + size, y};
    v2.texCoords = {1.0f, 0.0f};
    v2.texIndex = texIndex;

    Vertex v3;
    v3.position = {x, y};
    v3.texCoords = {0.0f, 0.0f};
    v3.texIndex = texIndex;

    return {v0, v1, v2, v3};
}

//Render the sprite with it's texture
void Renderer::Draw2D(GameObject* obj1, GameObject* obj2, glm::vec2 spriteSize, glm::vec3 color){
    // prepare transformations
    this->shader.Use();
    /*
    float vertices[] = { 
        // pos      // tex      //texture index
        -1.0f, -1.0f, 1.0f, 1.0f, 0.0f,
        0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        -1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f,

        1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 1.0f
    };
    */

    auto q1 = createQuad(-1.0f, -1.0f, 1.0f);
    auto q2 = createQuad(obj1->position.x, obj1->position.y, 0.0f);

    Vertex vertices[8];
    memcpy(vertices, q1.data(), q1.size() * sizeof(Vertex));
    memcpy(vertices + q1.size(), q2.data(), q2.size() * sizeof(Vertex));

    //Set dynamic vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, this->quadVBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    
    //set all quads renderered here to have a set scale passed down from param
    setSpriteSize(spriteSize);

    // render textured quad
    this->shader.SetVector3f("spriteColor", color);

    glBindTextureUnit(0, obj1->sprite.ID);
    glBindTextureUnit(1, obj2->sprite.ID);

    glBindVertexArray(this->quadVAO);
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, nullptr);
}

//Shader must be used before using this function
void Renderer::setSpriteSize(glm::vec2 spriteSize){

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));  // first translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)

    model = glm::translate(model, glm::vec3(0.5f * spriteSize.x, 0.5f * spriteSize.y, 0.0f)); // move origin of rotation to center of quad
    model = glm::rotate(model, glm::radians(0.0f), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
    model = glm::translate(model, glm::vec3(-0.5f * spriteSize.x, -0.5f * spriteSize.y, 0.0f)); // move origin back

    model = glm::scale(model, glm::vec3(spriteSize.x, spriteSize.y, 1.0f)); // last scale
    
    this->shader.SetMatrix4("transform", model);
}

//Set up the quad rendering
void Renderer::initRenderData(){
    // configure VAO/VBO/EBO
    /*
    float vertices[] = { 
        // pos      // tex      //texture index
        -1.0f, -1.0f, 1.0f, 1.0f, 0.0f,
        0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        -1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 0.0f,

        1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 1.0f
    };
    */
    unsigned int indices[] = {
        0, 1, 2, 2, 3, 1,
        4, 5, 6, 6, 7, 5
    };

    glCreateVertexArrays(1, &this->quadVAO);
    glCreateBuffers(1, &this->quadVBO);

    glBindVertexArray(this->quadVAO);

    glBindBuffer(GL_ARRAY_BUFFER, this->quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 1000, nullptr, GL_DYNAMIC_DRAW);

    //vertex attribute
    glEnableVertexArrayAttrib(this->quadVBO, 0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, position));
    
    //texture coordinates attribute
    glEnableVertexArrayAttrib(this->quadVBO, 1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, texCoords));

    //texture index attribute
    glEnableVertexArrayAttrib(this->quadVBO, 2);
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const void*)offsetof(Vertex, texIndex));

    glCreateBuffers(1, &this->quadEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->quadEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}