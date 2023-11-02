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
//! THIS CLASS SHOULDN"T BE USED AS IT WILL BE REFACTORED AT A LATER DATA
//TODO: Make batch rendering when rendering text

TextRenderer::TextRenderer(unsigned int width, unsigned int height,
 const char* vShaderFile, const char* fShaderFile) : texW(0), texH(0){
    //Load shader using Resource Manager
    this->textShader = ResourceManager::LoadShader(vShaderFile, fShaderFile, nullptr, "text");
    //Configure shader
    this->textShader.SetMatrix4("projection", glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f), true);
    this->textShader.SetInteger("text", 0);

    //Configure VAO/VBO for positioning and texturing
    initTextRenderingData();
}

TextRenderer::~TextRenderer(){
    //delete texture
    glDeleteTextures(1, &this->textureID);

    //delete quad buffer data 
    glDeleteVertexArrays(1, &this->quadVAO);
    glDeleteBuffers(1, &this->quadVBO);

    //delete any pointers
    delete[] this->quadBuffer;
    this->quadBufferPtr = nullptr;
    delete this->quadBufferPtr;
}

bool TextRenderer::loadFont(const char* filename, unsigned int fontsize){
    //declare local var that stores atlas rows
    unsigned int roww = 0;
	unsigned int rowh = 0;

    //init Characters array 
    memset(c, 0, sizeof(c));

    //Use free type to load font and set font size
    FT_Library ft;
    /* Initialize the FreeType2 library */
	if (FT_Init_FreeType(&ft)){
        std::cout << "ERROR: Couldn't load Freetype!" << std::endl;
        return false;
	}

    FT_Face face;
    /* Load a font */
	if (FT_New_Face(ft, filename, 0, &face)){
		std::cout << "ERROR: Couldn't load Fonb!" << std::endl;
        return false;
	}

    //Set up texture atlas and set up the characters

    //Set font size
    FT_Set_Pixel_Sizes(face, 0, fontsize);
    //Get font glyphs
	FT_GlyphSlot g = face->glyph;

    /* Find minimum size for a texture holding all visible ASCII characters */
    for (int i = 32; i < 128; i++){
        if (FT_Load_Char(face, i, FT_LOAD_RENDER)){
            fprintf(stderr, "Loading character %c failed!\n", i);
            continue;
        }
        if (roww + g->bitmap.width + 1 >= MAXATLASWIDTH){
            this->texW = std::max(this->texW, roww);
            this->texH += rowh;
            roww = 0;
            rowh = 0;
        }
        roww += g->bitmap.width + 1;
        rowh = std::max(rowh, g->bitmap.rows);
    }

    //Set atlas size in width and height
    texW = std::max(texW, roww);
    texH += rowh;

    /* Create a texture that will be used to hold all ASCII glyphs */
    //! This sets this texture to be at 32th textures, any texture binded at the 32th will cause texture conflicts
    glActiveTexture(GL_TEXTURE31);
    glGenTextures(1, &this->textureID);
    glBindTexture(GL_TEXTURE_2D, this->textureID);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, texW, texH, 0, GL_ALPHA, GL_UNSIGNED_BYTE, 0);

    /* We require 1 byte alignment when uploading texture data */
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    /* Clamping to edges is important to prevent artifacts when scaling */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    /* Linear filtering usually looks best for text */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    /* Paste all glyph bitmaps into the texture, remembering the offset */
    int ox = 0;
    int oy = 0;

    rowh = 0;

    for (int i = 32; i < 128; i++){
        if (FT_Load_Char(face, i, FT_LOAD_RENDER)){
            printf("ERROR: Loading character %c failed!\n", i);
            continue;
        }

        if (ox + g->bitmap.width + 1 >= MAXATLASWIDTH){
            oy += rowh;
            rowh = 0;
            ox = 0;
        }

        glTexSubImage2D(GL_TEXTURE_2D, 0, ox, oy, g->bitmap.width, g->bitmap.rows, GL_ALPHA, GL_UNSIGNED_BYTE, g->bitmap.buffer);
        c[i].ax = g->advance.x >> 6;
        c[i].ay = g->advance.y >> 6;

        c[i].bw = g->bitmap.width;
        c[i].bh = g->bitmap.rows;

        c[i].bl = g->bitmap_left;
        c[i].bt = g->bitmap_top;

        c[i].tx = ox / (float)texW;
        c[i].ty = oy / (float)texH;

        rowh = std::max(rowh, g->bitmap.rows);
        ox += g->bitmap.width + 1;
    }

    printf("MSG: Generated a %d x %d (%d kb) texture atlas\n", texW, texH, texW * texH / 1024);

    //Free Freetype resources
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
    //Succesfully managed to load the font
    std::cout << "MSG: Text Font loaded succesfully!\n";
    return true;
}

void TextRenderer::createTextQuad(const uint8_t* character, glm::vec2 pos, glm::vec2 scale, glm::vec4 color){

    //check if not over the vertex count
    if(this->vertexCount >= this->maxVertexCount){
        this->endBatch();
        this->flush();
        this->beginBatch();
    }

    //Generate character and set correct character using the atlas

    /* Calculate the vertex and texture coordinates */
    float x2 = pos.x + this->c[*character].bl * scale.x;
    float y2 = -pos.y - this->c[*character].bt * scale.y;
    float w = this->c[*character].bw * scale.x;
    float h = this->c[*character].bh * scale.y;

    /* Advance the cursor to the start of the next character */
    pos.x += this->c[*character].ax * scale.x;
    pos.y += this->c[*character].ay * scale.y;

    /* Skip glyphs that have no pixels and if glyphs have pixel then add to the quadbufferptr*/
    if (!w || !h){
        
        quadBufferPtr->position = glm::vec2(x2, -y2);
        quadBufferPtr->texCoords = glm::vec2(this->c[*character].tx, this->c[*character].ty);
        quadBufferPtr++;

        quadBufferPtr->position = glm::vec2(x2 + w, -y2);
        quadBufferPtr->texCoords = glm::vec2(this->c[*character].tx + this->c[*character].bw / this->texW, this->c[*character].ty);
        quadBufferPtr++;

        quadBufferPtr->position = glm::vec2(x2, -y2 - this->texH);
        quadBufferPtr->texCoords = glm::vec2(this->c[*character].tx, this->c[*character].ty + this->c[*character].bh / this->texH);
        quadBufferPtr++;

        quadBufferPtr->position = glm::vec2(x2 + this->texW, -y2);
        quadBufferPtr->texCoords = glm::vec2(this->c[*character].tx + this->c[*character].bw / this->texW, this->c[*character].ty);
        quadBufferPtr++;

        quadBufferPtr->position = glm::vec2(x2, -y2 - this->texH);
        quadBufferPtr->texCoords = glm::vec2(this->c[*character].tx, this->c[*character].ty + this->c[*character].bh / this->texH);
        quadBufferPtr++;

        quadBufferPtr->position = glm::vec2(x2 + this->texW, -y2 - this->texH);
        quadBufferPtr->texCoords = glm::vec2(this->c[*character].tx + this->c[*character].bw / this->texW, this->c[*character].ty + this->c[*character].bh / this->texH);
        quadBufferPtr++;        

        //Amount of triangles needed to render each character
        vertexCount += 6;
    } 
}

void TextRenderer::drawText(const char* text, glm::vec2 position, glm::vec2 scale, glm::vec4 color){
    //init the buffer
    this->beginBatch();

    //Set shader configs
    glBindTexture(GL_TEXTURE_2D, this->textureID);
    this->textShader.SetVector4f("textColor", color, true);
    this->textShader.SetInteger("text", 31, true);

    //Loop through each character and generate text buffer
    const uint8_t* p;
    for(p = (const uint8_t*)text; *p; p++){
        createTextQuad(p, position, scale, color);
    }

    //Set dynamic vertex buffer
    this->endBatch();
    //Draw the text
    this->flush();
}

void TextRenderer::initTextRenderingData(){
    //Configure buffers
    if(this->quadBuffer != nullptr)
        exit(-1);
    
    this->quadBuffer = new CharacterVertex[this->maxVertexCount];

    // configure VAO/VBO/EBO
    glCreateVertexArrays(1, &this->quadVAO);
    glCreateBuffers(1, &this->quadVBO);

    glBindVertexArray(this->quadVAO);

    glBindBuffer(GL_ARRAY_BUFFER, this->quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(CharacterVertex) * this->maxVertexCount, nullptr, GL_DYNAMIC_DRAW);

    //vertex attribute
    glEnableVertexArrayAttrib(this->quadVBO, 0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(CharacterVertex), (const void*)offsetof(CharacterVertex, position));
    
    //texture coordinates attribute
    glEnableVertexArrayAttrib(this->quadVBO, 1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(CharacterVertex), (const void*)offsetof(CharacterVertex, texCoords));  
}

void TextRenderer::beginBatch(){
    //Set buffer pointer
    this->quadBufferPtr = quadBuffer;

    //Call shader usage
    this->textShader.Use();
}

void TextRenderer::endBatch(){
    GLsizeiptr size = (uint8_t*)this->quadBufferPtr - (uint8_t*)this->quadBuffer;
    //set up dynamic buffer
    glBindBuffer(GL_ARRAY_BUFFER, this->quadVBO);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, quadBuffer);
}

void TextRenderer::flush(){
    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, vertexCount);

    //reset vertex count 
    this->vertexCount = 0;
}
//! THIS CLASS SHOULDN"T BE USED AS IT WILL BE REFACTORED AT A LATER DATA