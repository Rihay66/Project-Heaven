#pragma once

#ifndef RIGIDBODY_HPP
#define RIGIDBODY_HPP

// include box2d
#include <box2d/id.h>

/* types of physics body types that fufill a specific need
! Warning: Kinematic is yet to be fully implemented
*/
enum class BodyType {Static = 0, Dynamic, Kinematic };

// 2D rigidbody component
struct Rigidbody2D{
    BodyType Type = BodyType::Static;
    bool fixedRotation = false;

    // storage for runtime body
    b2BodyId runtimeBody = b2_nullBodyId;

    // constructors
    Rigidbody2D() = default;
    Rigidbody2D(const Rigidbody2D&) = default;
};


#endif