#pragma once

#ifndef TEXTURE_HPP
#define TEXTURE_HPP

// include GLM
#include <glm/glm.hpp>

// include standard array library
#include <array>

// 2D texture component
struct Texture2D {
    int texIndex;
    std::array<glm::vec2, 4> texCoords = {{
        {0.0f, 0.0f},
        {1.0f, 0.0f},
        {1.0f, 1.0f},
        {0.0f, 1.0f}
    }};
};

#endif