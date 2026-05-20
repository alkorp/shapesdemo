#include <SFML/Graphics.hpp>

#include "common.hpp"
#include "ecs.hpp"
#include "shapes/circle.hpp"
#include "shapes/rectangle.hpp"
#include "shapes/triangle.hpp"
#include "systems/animation.hpp"
#include "systems/render.hpp"
#include "systems/transform.hpp"

// Draw demo shapes, set up position and enable animation
void createDemoEntities(Registry& registry, Point window_size) {
    const int n = 5;
    const std::array<Point, 3> triangle_points {{{0, 0}, {100, 0}, {50, 50}}};
    const int rectangle_width = 75;
    const int rectangle_height = 50;

    auto dx = window_size.x / n;
    auto dy = window_size.y / n;
    for (int i = 0; i < n; ++i) {
        auto triangle = Triangle::create(registry, triangle_points);
        TransformSystem::setPosition(registry, triangle, {i * dx, i * dy});
        AnimationSystem::animateEntity(registry, triangle);

        auto rectangle = Rectangle::create(registry, rectangle_width, rectangle_height);
        TransformSystem::setPosition(registry, rectangle, {i * dx, window_size.y - i * dy});
        AnimationSystem::animateEntity(registry, rectangle);
    }
}

int main() {
    const int window_width = 800;
    const int window_height = 600;
    sf::RenderWindow window(sf::VideoMode({window_width, window_height}), "Shapes demo");
    window.setFramerateLimit(30);

    Registry registry;
    RenderSystem render_system(window);
    createDemoEntities(registry, {window_width, window_height});
    auto circle = Circle::create(registry, CircleData{.center{300, 300}, .radius = 50}, 100);
    int circle_vertex_count = 3;

    // run the program as long as the window is open
    while (window.isOpen()) {
        Circle::setVertexCount(registry, circle, std::abs(circle_vertex_count - 20) + 3);
        circle_vertex_count = (circle_vertex_count + 1) % 40;

        AnimationSystem::update(registry, {window_width, window_height});

        // check all the window's events that were triggered since the last
        // iteration of the loop
        while (const std::optional event = window.pollEvent()) {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>()) window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        render_system.draw_all(registry);

        // end the current frame
        window.display();
    }

    return 0;
}
