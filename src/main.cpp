#include <SFML/Graphics.hpp>
#include "kinematics.hpp"
#include "newton.hpp"

enum Mode {
    KINEMATICS,
    NEWTON
};

int main(){
    sf::RenderWindow window(sf::VideoMode({800,600}),  "Physics Mode Switcher");
    Mode mode = KINEMATICS;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            else if (auto keyEvent = event->getIf<sf::Event::KeyPressed>(); keyEvent != nullptr)
            {
                if (keyEvent->code == sf::Keyboard::Key::Space)
                {
                    mode = (mode == KINEMATICS) ? NEWTON : KINEMATICS;
                }
            }
        }

        window.clear();

        if (mode == KINEMATICS)
        {
            sf::CircleShape circle(50.f);
            circle.setFillColor(sf::Color::Green);
            circle.setPosition({100, 100});
            window.draw(circle);
        }
        else
        {
            sf::RectangleShape rect(sf::Vector2f(100.f, 50.f));
            rect.setFillColor(sf::Color::Red);
            rect.setPosition({200, 200});
            window.draw(rect);
        }
        //window.draw(label);
        window.display();
    }
}