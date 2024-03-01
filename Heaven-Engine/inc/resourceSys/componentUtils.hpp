#pragma once

#ifndef COMPONENTUTILS_HPP
#define COMPONENTUTILS_HPP

#include <glm/glm.hpp>
#include <algorithm>

// types of triggers that fufill a specific need
enum class TriggerType {Enter = 0, Stay, Exit};
/* types of physics body types that fufill a specific need
* Warning: Kinematic is yet to be fully implemented
*/
enum class BodyType {Static = 0, Dynamic, Kinematic };

// physics components
struct Rigidbody{
    BodyType Type = BodyType::Dynamic;
    bool fixedRotation = false;

    // storage for runtime
    void* runtimeBody = nullptr;
    // constructors
    Rigidbody() = default;
    Rigidbody(const Rigidbody&) = default;
};

struct BoxCollider{
    glm::vec2 offset = {0.0f, 0.0f};
    glm::vec2 size = {0.5f, 0.5f};
    float rotationOffset = 0.0f;

    float density = 1.0f;
    float friction = 0.5f;
    float restitution = 0.0f;
    float restitutionThreshold = 0.5f;

    // storage for runtime
    void* runtimeBody = nullptr;

    // constructors
    BoxCollider() = default;
    BoxCollider(const BoxCollider&) = default;
};

#endif