#include <engine/textRenderer.hpp>
#include <resourceSys/resourceManager.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

//Check platform and then grab the Freetype library
#ifdef __unix__ //Linux platform
    #include <freetype2/ft2build.h>
    #include FT_FREETYPE_H
#elif defined(_WIN32) || defined(WIN32) //Windows platform
    #include <ft2build.h>
    #include FT_FREETYPE_H
#endif

//TODO: When creating the texture use the glad given id num to bind the texture
//TODO: Make batch rendering when rendering text

TextRenderer::TextRenderer(unsigned int width, unsigned int height,
 const char* vShaderFile, const char* fShaderFile){
    //Load shader using Resource Manager
    this->textShader = ResourceManager::LoadShader(vShaderFile, fShaderFile, nullptr, "text");
    //Configure shader
    this->textShader.SetMatrix4("projection", glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f), true);

    //Configure texture indexing
    auto loc = glGetUniformLocation(this->textShader.ID, "text");
    
    int samplers[128];

    //set up samplers array
    for(int i = 0; i < 128; i++){
        samplers[i] = i;
    }

    glUniform1iv(loc, 128, samplers);

    //Configure VAO/VBO/EBO for positioning and texturing
    initTextRenderingData();
    
}

TextRenderer::~TextRenderer(){

}

void TextRenderer::initTextRenderingData(){
    //Configure buffers
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