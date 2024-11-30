#pragma once

#ifndef BOXCOLLIDER_HPP
#define BOXCOLLIDER_HPP

// include GLM
#include <glm/glm.hpp>

// 2D box collider component
struct BoxCollider2D{
    glm::vec2 offset = {0.0f, 0.0f};
    glm::vec2 size = {0.5f, 0.5f};
    float rotationOffset = 0.0f;

    float density = 1.0f;
    float friction = 0.5f;
    float restitution = 0.0f;
    float restitutionThreshold = 0.5f;
};

#endif