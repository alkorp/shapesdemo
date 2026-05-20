#pragma once

#include <array>

#include "../common.hpp"
#include "../ecs.hpp"


class Triangle {
public:
    static Entity create(Registry& registry, const std::array<Point, 3>& points);
};
