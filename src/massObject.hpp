#ifndef MASS_OBJECT_HPP
#define MASS_OBJECT_HPP
#include <vector>
#include <SFML/Graphics.hpp>

class massObject : public sf::CircleShape
{

public:
    massObject();

    float getMass() const;

    sf::Vector2f getPosition() const;

private:
    sf::CircleShape circle;

    std::vector<sf::Color> colors;

    float mass;

    sf::Vector2f position;

    float euclidDistance;

    sf::Vector2f distanceVector;

    sf::Vector2f normalizedVector;
};

#endif
