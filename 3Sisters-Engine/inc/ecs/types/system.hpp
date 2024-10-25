#pragma once

#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <set>

#include <ecs/types/entity.hpp>

/* System contains a set of entities with certain
signatures that it can iterate through
*/
class System{
    public:
        std::set<Entity> entities;
};

#endif