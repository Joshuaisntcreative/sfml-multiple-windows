#include "kinematics.hpp"
#include <iostream>
#include <cmath>
void drawKinematics(sf::RenderWindow &window)
{
    sf::CircleShape sun(30.f);
    sun.setFillColor(sf::Color::White);
    sun.setPosition({300, 300});
    sun.setOutlineColor(sf::Color::Yellow);
    sun.setOutlineThickness(5.f);

    sf::CircleShape earth(10.f);
    earth.setFillColor(sf::Color::White);
    earth.setPosition({700, 300});
    earth.setOutlineColor(sf::Color::Blue);
    earth.setOutlineThickness(5.f);

    const double bigG = 6.674e-3f;

    double massOfEarth = 5.f;
    double massOfSun = 50.f;
    float velocity = 0.0f;

    sf::Clock clock;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        float deltaTime = clock.restart().asSeconds();

        massOfSun += 5.f;
        float distance = earth.getPosition().x - sun.getPosition().x;


        float gravitationalForce = (bigG * massOfEarth * massOfSun)/distance * distance;
        float centripetalAcceleration = gravitationalForce / massOfEarth;
        velocity -= sqrt(centripetalAcceleration/distance);
        float position = earth.getPosition().x;
        position += velocity*deltaTime;
        earth.setPosition({position,300.f});

        window.clear();
        window.draw(earth);
        window.draw(sun);
        window.display();
    }
}