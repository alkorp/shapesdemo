#pragma once

#include <SFML/Graphics.hpp>

#include "../ecs.hpp"


struct RenderData {
    sf::VertexArray vertices;
};

class RenderSystem {
public:
    explicit RenderSystem(sf::RenderWindow& window): window_{window} {};

    void draw_all(Registry& registry) {
        for(auto&& [entity, data]: registry.view<RenderData>()) {
            auto transform = registry.getComponent<Transform>(entity);
            sf::RenderStates rs;
            if (transform) {
                rs.transform.translate(sf::Vector2f(transform->offset.x, transform->offset.y));
            }
            window_.draw(data.vertices, rs);
        }
    }
private:
    sf::RenderWindow& window_;

};
