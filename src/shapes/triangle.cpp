#include "triangle.hpp"

#include "../systems/render.hpp"


Entity Triangle::create(Registry& registry, const std::array<Point, 3>& points) {
    Entity entity = registry.create();
    registry.addComponent<Transform>(entity);
    RenderData& render_data = registry.addComponent<RenderData>(entity);
    render_data.vertices.resize(3);
    render_data.vertices.setPrimitiveType(sf::PrimitiveType::Triangles);

    int idx = 0;
    for (const Point& p: points) {
        render_data.vertices[idx++].position = sf::Vector2f(p.x, p.y);
    }

    return entity;
}