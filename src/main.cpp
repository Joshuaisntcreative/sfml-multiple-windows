#include <SFML/Graphics.hpp>
#include "kinematics.hpp"
#include "newton.hpp"
#include "tension.hpp"
#include "collision.hpp"

enum Mode {
    KINEMATICS,
    NEWTON,
    TENSION,
    COLLISION
};

int main(){
    sf::RenderWindow window(sf::VideoMode({1920,1080}),  "Physics Mode Switcher");
    //Change this mode to the given enums provided above to alternate between simulations
    Mode mode = COLLISION;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear();

        switch(mode){
        case KINEMATICS:
            drawKinematics(window);
            break;
        case NEWTON:
            drawNewton(window);
            break;
        case TENSION:
            drawTension(window);
            break;
        case COLLISION:
            drawCollision(window);
            break;
        }
        //window.draw(label);
        window.display();
    }
}