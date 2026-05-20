#pragma once

#include "../common.hpp"
#include "../ecs.hpp"

struct CircleData {
    Point center;
    int radius;
};

class Circle {
public:
    static Entity create(Registry& registry, const CircleData& data, int vertex_count = 20);
    static bool setVertexCount(Registry& registry, Entity entity, int vertexCount);
};
