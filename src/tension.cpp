#include "tension.hpp"
#include <iostream>
#include <cmath>
void drawTension(sf::RenderWindow& window)
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


    sf::Clock clock;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        window.draw(earth);
        window.draw(sun);
        window.display();
    }
}