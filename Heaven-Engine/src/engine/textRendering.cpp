#include <engine/textRenderer.hpp>

#include <iostream>

#ifdef __unix__ //Linux platform
    #include <freetype2/ft2build.h>
    #include FT_FREETYPE_H
#elif defined(_WIN32) || defined(WIN32) //WIndows platform
    #include <ft2build.h>
    #include FT_FREETYPE_H
#endif


TextRenderer::TextRenderer(unsigned int width, unsigned int height){
    
}

TextRenderer::~TextRenderer(){

}