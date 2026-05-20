#include "animation.hpp"

#include "render.hpp"

namespace {
struct AnimationData {
    Point delta;
};

uint8_t toByte(float v) {
    if (v > 255) v = 255;
    if (v < 0) v = 0;
    return static_cast<uint8_t>(v);
}

sf::Color getPointColor(Point point, Point movement_area_size) {
    auto red = toByte(static_cast<float>(point.x) * 0xFFU / movement_area_size.x);
    auto green = toByte(static_cast<float>(point.y) * 0xFFU / movement_area_size.y);
    auto blue = 0xFF - std::abs(red - green);
    return sf::Color(red, green, blue);
}
}  // namespace

void AnimationSystem::animateEntity(Registry& registry, Entity entity) {
    auto& data = registry.addComponent<AnimationData>(entity);
    data.delta = {.x = 3, .y = 3};
}

void AnimationSystem::update(Registry& registry, Point movement_area_size) {
    for (auto&& [entity, animation_data] : registry.view<AnimationData>()) {
        auto position = registry.getComponent<Transform>(entity);
        if (!position) continue;

        position->offset.x += animation_data.delta.x;
        position->offset.y += animation_data.delta.y;

        if (position->offset.x > movement_area_size.x) {
            position->offset.x = movement_area_size.x;
            animation_data.delta.x *= -1;
        } else if (position->offset.x < 0) {
            position->offset.x = 0;
            animation_data.delta.x *= -1;
        }
        if (position->offset.y > movement_area_size.y) {
            position->offset.y = movement_area_size.y;
            animation_data.delta.y *= -1;
        } else if (position->offset.y < 0) {
            position->offset.y = 0;
            animation_data.delta.y *= -1;
        }

        auto render_data = registry.getComponent<RenderData>(entity);
        if (!render_data) continue;
        auto color = getPointColor(position->offset, movement_area_size);
        for (int i = 0; i < render_data->vertices.getVertexCount(); ++i) {
            render_data->vertices[i].color = color;
        }
    }
};
