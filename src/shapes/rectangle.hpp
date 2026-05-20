#pragma once

#include <array>

#include "../common.hpp"
#include "../ecs.hpp"

class Rectangle {
public:
    static Entity create(Registry& registry, int width, int height);
};
