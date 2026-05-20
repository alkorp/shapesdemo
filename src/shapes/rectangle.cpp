#include "rectangle.hpp"

#include "../systems/render.hpp"

Entity Rectangle::create(Registry& registry, int width, int height) {
    auto entity = registry.create();
    registry.addComponent<Transform>(entity);
    auto& render_data = registry.addComponent<RenderData>(entity);

    render_data.vertices.resize(5);
    render_data.vertices.setPrimitiveType(sf::PrimitiveType::TriangleStrip);
    render_data.vertices[0].position = sf::Vector2f(0, 0);
    render_data.vertices[1].position = sf::Vector2f(width, 0);
    render_data.vertices[2].position = sf::Vector2f(width, height);
    render_data.vertices[3].position = sf::Vector2f(0, height);
    render_data.vertices[4].position = sf::Vector2f(0, 0);

    return entity;
}