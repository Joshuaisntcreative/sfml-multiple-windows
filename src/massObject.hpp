#pragma once
#include <SFML/Graphics.hpp>

struct MassObject
{
    sf::CircleShape shape;
    float mass = 0.f;
    MassObject(float radius, float mass1, sf::Vector2f position, sf::Color color = sf::Color::White)
    {
        mass = mass1;
        shape.setRadius(radius);
        shape.setOrigin({radius, radius}); // center the origin
        shape.setPosition(position);
        shape.setFillColor(color);
    }

    void draw(sf::RenderWindow& window) const {
        window.draw(shape);
    }

    // Optional: Get the position of the center
    sf::Vector2f getPosition() const {
        return shape.getPosition();
    }

    // Optional: Set a new position
    void setPosition(sf::Vector2f pos) {
        shape.setPosition(pos);
    }
};
