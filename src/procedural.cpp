#include "procedural.hpp"
#include "supportingFiles/functions.hpp"
#include "supportingFiles/Gui.hpp"
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
    Gui gui = Gui();
    sf::Mouse::Button button;
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            //mouse is clicked
            if (event->is<sf::Event::MouseButtonPressed>())
            {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
                {
                    gui.addMass();
                }
            }
        }

        

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        gui.update(mousePos, button);
        window.clear();
        window.draw(gui);
        window.display();
    }
}