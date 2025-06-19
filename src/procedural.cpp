#include "procedural.hpp"
#include "functions.hpp"
#include "massObject.hpp"
#include <cmath>
#include <iostream>

// Gradual force simulation to overcome static friction and accelerate
void drawProcedural(sf::RenderWindow& window) {


    sf::Font font;
        if (!font.openFromFile("C:\\Users\\jjthu\\Downloads\\COMPUTER SCIENCE\\NON_SCHOOL\\cmake projects\\sfml-multiple-windows\\dependencies\\ROCK.TTF")) {
        std::cerr << "Error loading font" << std::endl;
    }
    sf::Text text(font, "Hello", 20);
    text.setPosition({10, 10});

    float totalTime = 0.f;
    sf::Clock clock;


    MassObject mass1(20.f, 5.f, {400.f, 300.f}, sf::Color::Green);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

    float deltaTime = clock.restart().asSeconds();
    totalTime += deltaTime;
    if(totalTime >= 5.f)
    {
        text.setString("Time exceeded 5 seconds");
    }

        window.clear();
        window.draw(text);
        mass1.draw(window);
        window.display();
    }
}