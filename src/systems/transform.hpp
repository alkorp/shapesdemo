#pragma once

#include "../common.hpp"
#include "../ecs.hpp"

class TransformSystem {
public:
    static void setPosition(Registry& registry, Entity entity, Point position) {
        auto transform_data = registry.getComponent<Transform>(entity);
        if (transform_data) {
            transform_data->offset = position;
        }
    }
    static void move(Registry& registry, Entity entity, Point offset) {
        auto transform_data = registry.getComponent<Transform>(entity);
        if (transform_data) {
            transform_data->offset.x += offset.x;
            transform_data->offset.y += offset.y;
        }
    }
};
