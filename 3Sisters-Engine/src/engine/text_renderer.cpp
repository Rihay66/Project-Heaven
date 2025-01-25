#include <engine/text_renderer.hpp>

// additional GLM libraries
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// standard library for debug outputs
#include <iostream>

// include ResourceManager
#include <resourceSystems/managers/resource_manager.hpp>

// check platform and then grab the Freetype library
#ifdef __unix__ // Linux/Unix platform
    #include <freetype2/ft2build.h>
    #include FT_FREETYPE_H
#elif defined(_WIN32) || defined(WIN32) // Windows platform
    #include <ft2build.h>
    #include FT_FREETYPE_H
#endif

// init static variables
unsigned int    TextRenderer::VAO;
unsigned int    TextRenderer::VBO;
Shader          TextRenderer::textShader;
bool            TextRenderer::isAutoClearSet = false;

//TODO: Refactor text renderer to use a batch rendering solution

void TextRenderer::Init(Shader& shader){
    // when auto clear is set, stop re-initializing rendering data
    if(isAutoClearSet){
        std::cout << "Warning: Initialization of Text Renderer being called more than once!\n";
        return;
    }

    // set up auto clear
    setUpAutoClear();

    // set shader
    textShader = shader;

    // configure VAO/VBO for positioning and texturing
    initTextRenderingData();
}

void TextRenderer::DrawText(std::map<char, Character>& chars, std::string text, glm::vec2 position, glm::vec2 scale, float rotation, glm::vec4 color){
    // check if the text renderer has been set  
    if(!isAutoClearSet){
        std::cout << "ERROR: Missing text render data initialization!\n";
        return;
    }

    // set the shader and set the textColor
    textShader.SetVector4f("textColor", color, true);

    // bind this VAO
    glBindVertexArray(VAO);

    // iterate through all characters
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++) 
    {
        Character ch = chars[*c];

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
        glBindTextureUnit(0, ch.TextureID);
        // update content of VBO memory
        glNamedBufferSubData(VBO, 0, sizeof(vertices), vertices);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        position.x += (ch.Advance >> 6) * scale.x; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }

    // rebind non-font textures
    ResourceManager::BindTextures();
}

void TextRenderer::initTextRenderingData(){
    // configure VAO/VBO for texture quads
    glCreateVertexArrays(1, &VAO);
    glCreateBuffers(1, &VBO);
    
    glNamedBufferData(VBO, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
    glVertexArrayVertexBuffer(VAO, 0, VBO, 0, 4 * sizeof(float));

    glEnableVertexArrayAttrib(VAO, 0);
    glVertexArrayAttribBinding(VAO, 0, 0);
    glVertexArrayAttribFormat(VAO, 0, 4, GL_FLOAT, GL_FALSE, 0);
}

void TextRenderer::clear(){
    // delete quad buffer data 
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void TextRenderer::setUpAutoClear(){
    // set up on exit to call the Clear()
    if(!isAutoClearSet && std::atexit(clear) == 0){
        isAutoClearSet = true; // disable calling this function again
    }
}