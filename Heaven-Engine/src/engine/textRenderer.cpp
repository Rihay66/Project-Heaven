#include <engine/textRenderer.hpp>
#include <resourceSys/resourceManager.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

//Check platform and then grab the Freetype library
#ifdef __unix__ //Linux platform
    #include <freetype2/ft2build.h>
    #include FT_FREETYPE_H
#elif defined(_WIN32) || defined(WIN32) //Windows platform
    #include <ft2build.h>
    #include FT_FREETYPE_H
#endif

//TODO: Redo text renderer to use a batch rendering solution

TextRenderer::TextRenderer(unsigned int width, unsigned int height,
 Shader& shader) : textShader(shader){
    //Create projection
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height));

    //Configure shader
    this->textShader.SetMatrix4("projection", projection, true);

    //Configure VAO/VBO for positioning and texturing
    initTextRenderingData();
}

TextRenderer::~TextRenderer(){
    //delete quad buffer data 
    glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(1, &this->VBO);
}

void TextRenderer::drawText(std::string text, glm::vec2 position, glm::vec2 scale, glm::vec4 color){
    //Set the shader
    this->textShader.SetVector4f("textColor", color, true);

    //Bind this VAO
    glBindVertexArray(this->VAO);

    // iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++) 
    {
        ResourceManager::Character ch = ResourceManager::Characters[*c];

        float xpos = position.x + ch.Bearing.x * scale.x;
        float ypos = position.y - (ch.Size.y - ch.Bearing.y) * scale.y;

        float w = ch.Size.x * scale.x;
        float h = ch.Size.y * scale.y;
        // update VBO for each character
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },            
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }           
        };
        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        position.x += (ch.Advance >> 6) * scale.x; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }
}

void TextRenderer::initTextRenderingData(){
    // configure VAO/VBO for texture quads
    glCreateVertexArrays(1, &this->VAO);
    glBindVertexArray(this->VAO);

    glCreateBuffers(1, &this->VBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}