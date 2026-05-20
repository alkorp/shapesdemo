#include "circle.hpp"

#include "../systems/render.hpp"

namespace {
sf::Vector2f getPoint(Point center, int radius, int index, int point_count) {
    const sf::Angle angle = static_cast<float>(index) / static_cast<float>(point_count) * sf::degrees(360.f) - sf::degrees(90.f);
    return sf::Vector2f(center.x, center.y) + sf::Vector2f(radius, angle);
}

void fillVertices(sf::VertexArray& vertices, const CircleData& data, int vertex_count) {
    vertices.resize(vertex_count + 2);
    vertices.setPrimitiveType(sf::PrimitiveType::TriangleFan);
    
    for (std::size_t i = 0; i < vertex_count; ++i)
        vertices[i + 1].position = getPoint(data.center, data.radius, i, vertex_count);
        
    vertices[vertex_count + 1].position = vertices[1].position;
    vertices[0].position = sf::Vector2f(data.center.x, data.center.y);
}

} // namespace


Entity Circle::create(Registry& registry, const CircleData& data, int vertex_count) {
    Entity entity = registry.create();
    registry.addComponent<CircleData>(entity) = data;
    registry.addComponent<Transform>(entity);

    RenderData& render_data = registry.addComponent<RenderData>(entity);
    fillVertices(render_data.vertices, data, vertex_count);
    
    return entity;
}

bool Circle::setVertexCount(Registry& registry, Entity entity, int vertex_count) {
    auto circle_data = registry.getComponent<CircleData>(entity);
    if (!circle_data) return false;

    auto render_data = registry.getComponent<RenderData>(entity);
    if (!render_data) return false;

    fillVertices(render_data->vertices, *circle_data, vertex_count);
    return true;
}
