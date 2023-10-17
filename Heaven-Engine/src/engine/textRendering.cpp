#include <engine/textRenderer.hpp>

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

TextRenderer::TextRenderer(unsigned int width, unsigned int height){
    
}

TextRenderer::~TextRenderer(){

}