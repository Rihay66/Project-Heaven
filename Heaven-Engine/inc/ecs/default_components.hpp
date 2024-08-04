#pragma once

#ifndef DEFAULT_COMPONENTS_HPP
#define DEFAULT_COMPONENTS_HPP

// include GLM
#include <glm/glm.hpp>

// types of triggers that fufill a specific need
enum class TriggerType {Enter = 0, Stay, Exit};

/* types of physics body types that fufill a specific need
* Warning: Kinematic is yet to be fully implemented
*/
enum class BodyType {Static = 0, Dynamic, Kinematic };

// transform component
struct Transform{
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
};

// 2D transform component
struct Transform2D{
    glm::vec2 position;
    float rotation;
    glm::vec2 scale;
};

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

    // constructors
    BoxCollider() = default;
    BoxCollider(const BoxCollider&) = default;
};

#endif