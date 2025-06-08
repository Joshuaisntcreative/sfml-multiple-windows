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

    sf::CircleShape moon(5.f);
    moon.setFillColor(sf::Color::White);
    moon.setPosition({500, 300});
    moon.setOutlineColor(sf::Color::Red);
    moon.setOutlineThickness(5.f);

    const double bigG = 6.674e-3f;

    double massOfMoon = 2.f;
    double massOfEarth = 5.f;
    double massOfSun = 5.34e9f;
    sf::Vector2f velocity = {0.f, -200.f};
    sf::Vector2f moonVelocity = {0.f, -200.f};

    sf::Clock clock;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        float deltaTime = clock.restart().asSeconds();
        sf::Vector2f position = earth.getPosition();

        sf::Vector2f moonPosition = moon.getPosition();
        sf::Vector2f moonDirection = sun.getPosition() - moon.getPosition();
        float moonDistance = sqrt(pow(moonDirection.x,2) + pow(moonDirection.y,2));

        sf::Vector2f direction = sun.getPosition() - earth.getPosition();
        float distance = sqrt(pow(direction.x,2) + pow(direction.y,2));

        float gravitationalForce = -(bigG * massOfEarth * massOfSun)/(distance * distance);
        float moonGravitationForce = -(bigG * massOfMoon * massOfSun)/(moonDistance * moonDistance);



        sf::Vector2f normalizedDirection = direction / distance;

        sf::Vector2f normalizedMoonDirection = moonDirection/ moonDistance;
        sf::Vector2f moonAcceleration = normalizedMoonDirection * static_cast<float>(gravitationalForce)/static_cast<float>(massOfMoon);
        sf::Vector2f acceleration = normalizedDirection * (static_cast<float>(gravitationalForce)/static_cast<float>(massOfEarth));


        moonVelocity -= moonAcceleration * deltaTime;
        moonPosition += moonVelocity * deltaTime;

        velocity -= acceleration * deltaTime;
        position += velocity * deltaTime;

        earth.setPosition(position);
        moon.setPosition(moonPosition);

        window.clear();
        window.draw(earth);
        window.draw(moon);
        window.draw(sun);
        window.display();
    }
}