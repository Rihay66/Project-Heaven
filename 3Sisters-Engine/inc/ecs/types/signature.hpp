#pragma once

#ifndef SIGNATURE_HPP
#define SIGNATURE_HPP

#include <ecs/types/component.hpp>
#include <bitset>

/* type alias to define a signature which allows for
tracking which components and entity "has"
*/
using Signature = std::bitset<MAX_COMPONENTS>;

#endif