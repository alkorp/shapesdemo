#pragma once

#include "../common.hpp"
#include "../ecs.hpp"

class AnimationSystem {
public:
    static void animateEntity(Registry& registry, Entity entity);
    static void update(Registry& registry, Point movement_area_size);
};
