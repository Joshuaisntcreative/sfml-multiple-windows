#include "newton.hpp"
#include <iostream>

// Gradual force simulation to overcome static friction and accelerate
void drawNewton(sf::RenderWindow& window) {
    sf::RectangleShape platForm(sf::Vector2f(745.f, 50.f));
    platForm.setFillColor(sf::Color::Transparent);
    platForm.setOutlineColor(sf::Color::Red);
    platForm.setOutlineThickness(5.f);
    platForm.setPosition({5, 500});

    sf::RectangleShape box(sf::Vector2f(50.f, 50.f));
    box.setFillColor(sf::Color::White);
    box.setPosition({5, 445});
    box.setOutlineThickness(5.f);
    box.setOutlineColor(sf::Color::Blue);

    const float mass = 50.0f;                   // kg
    const float gravity = 9.81f;                // m/s²
    const float mu_static = 0.4f;               // coefficient of static friction
    const float mu_kinetic = 0.3f;              // coefficient of kinetic friction
    const float normalForce = mass * gravity;   // N
    const float maxStaticFriction = mu_static * normalForce;

    float appliedForce = 0.0f;     // gradually increasing
    float velocity = 0.0f;         // in m/s
    float positionX = box.getPosition().x;

    sf::Clock clock;

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();

        // Gradually increase applied force (simulate pushing harder)
        appliedForce += 10.0f * deltaTime; // N/s

        float netForce = 0.0f;

        if (appliedForce <= maxStaticFriction) {
            netForce = 0.0f; // Not enough to move yet
            std::cout << "Static friction resisting: " << appliedForce << " N\n";
        } else {
            // Kinetic motion: F_net = F_applied - F_kinetic
            float kineticFriction = mu_kinetic * normalForce;
            netForce = appliedForce - kineticFriction;
            float acceleration = netForce / mass;
            velocity += acceleration * deltaTime;
            positionX += velocity * deltaTime;

            std::cout << "Moving. Velocity: " << velocity << " m/s | Net Force: " << netForce << " N\n";
        }

        box.setPosition({positionX, 445.f});

        window.clear();
        window.draw(platForm);
        window.draw(box);
        window.display();
    }
}