#pragma once

#ifndef RIGIDBODY_UTILS_HPP
#define RIGIDBODY_UTILS_HPP

// include GLM
#include <glm/glm.hpp>

/* apply a given force to the given body at the body world position
* Note: also wakes the body 
*/
void ApplyForce(glm::vec2 force, void* body);

/* apply a given velocity to the given body

*/
void ApplyLinearVelocity(glm::vec2 velocity, void* body);

/* explicitly set the velocity to the given body

*/
void SetLinearVelocity(glm::vec2 velocity, void* body);

/* explicitly set the Y-axias velocity to the given body

*/
void SetYLinearVelocity(float y, void* body);

/* explicitly set the X-axias velocity to the given body

*/
void SetXLinearVelocity(float x, void* body);

#endif