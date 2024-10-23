#pragma once

#ifndef RESOURCE_TYPES_HPP
#define RESOURCE_TYPES_HPP

// include standard library
#include <array>

// include GLM
#include <glm/glm.hpp>

// holds all state information relevant to a character as loaded using FreeType
struct Character {
    unsigned int TextureID; // ID handle of the glyph texture
    glm::ivec2 Size;        // size of glyph
    glm::ivec2 Bearing;     // offset from baseline to left/top of glyph
    unsigned int Advance;   // horizontal offset to advance to next glyph
};

// define a sub texture that contains oordinates of a specific texture
struct SubTexture {
    std::array<glm::vec2, 4> TexCoords;
};

#endif 
