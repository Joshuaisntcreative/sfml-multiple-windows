#include "tension.hpp"
#include <iostream>
#include <cmath>

sf::Vector2f normalize(const sf::Vector2f& vec) {
    float len = std::sqrt(vec.x * vec.x + vec.y * vec.y);
    if (len != 0)
        return vec / len;
    return sf::Vector2f(0.f, 0.f); // Avoid division by zero
}
//"To find the force ON object A FROM object B, do: B - A"
float distance(const sf::Vector2f& vec1, sf::Vector2f& vec2){
    float distance = sqrt(pow(vec1.x - vec2.x,2) + pow(vec1.y - vec2.y,2));
    return distance;
}


void drawTension(sf::RenderWindow& window)
{
    sf::CircleShape sun1(30.f);
    sun1.setFillColor(sf::Color::White);
    sun1.setPosition({930, 300});
    sun1.setOutlineColor(sf::Color::Yellow);
    sun1.setOutlineThickness(5.f);

    sf::CircleShape sun2(30.f);
    sun2.setFillColor(sf::Color::White);
    sun2.setPosition({1520, 800});
    sun2.setOutlineColor(sf::Color::Green);
    sun2.setOutlineThickness(5.f);



    sf::CircleShape sun3(30.f);
    sun3.setFillColor(sf::Color::White);
    sun3.setPosition({340, 800});
    sun3.setOutlineColor(sf::Color::Blue);
    sun3.setOutlineThickness(5.f);

    //gravitational variables
    const float bigG = 6.674e-2;
    float massSun1 = 500.f;
    float massSun2 = 800.f;
    float massSun3 = 800.f;

    sf::Vector2f velocity1 = {0.f, 0.f};
    sf::Vector2f velocity2 = {0.f, 0.f};
    sf::Vector2f velocity3 = {0.f, 0.f};

    sf::Vector2f position1 = sun1.getPosition();
    sf::Vector2f position2 = sun2.getPosition();
    sf::Vector2f position3 = sun3.getPosition();

    sf::Clock clock;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

    float deltaTime = clock.restart().asSeconds();


    //raw distance points between the masses
    sf::Vector2f sun1_2distance = sun1.getPosition() - sun2.getPosition();
    sf::Vector2f sun1_3distance = sun1.getPosition() - sun3.getPosition();
    sf::Vector2f sun2_3distance = sun2.getPosition() - sun3.getPosition();
    sf::Vector2f sun3_2distance = sun3.getPosition() - sun2.getPosition();
    sf::Vector2f sun2_1distance = sun2.getPosition() - sun1.getPosition();
    sf::Vector2f sun3_1distance = sun3.getPosition() - sun1.getPosition();
    //you want the length from 1 TO 3 so you compute 3 - 1 in the function
    float length1_3 = distance(position3, position1);
    //length from 1 TO 2 so you compute 2 - 1 in the function
    float length1_2 = distance(position2, position1);
    //length from 2 to 3 so you compute 3 - 2 in the function
    float length2_3 = distance(position3, position2);

    float length3_2 = distance(position2, position3);

    float length2_1 = distance(position1, position2);

    float length3_1 = distance(position1, position3);

    //we are going to invert these values for each respective mass when the time is needed dw :D
    //scratch that we might as well not confuse ourselves :D

    //"direction vectors for each vector"
    auto normalized1_3 = normalize(sun1_3distance);
    auto normalized2_3 = normalize(sun2_3distance);
    auto normalized1_2 = normalize(sun1_2distance); 
    auto normalized3_2 = normalize(sun3_2distance);
    auto normalized2_1 = normalize(sun2_1distance);
    auto normalized3_1 = normalize(sun3_1distance);



    //all of the forces that currently exist in the system
    float force1_2 = (bigG * massSun1 * massSun2)/(length1_2) * (length1_2);
    float force1_3 = (bigG * massSun1 * massSun3)/(length1_3) * (length1_3);
    float force2_3 = (bigG * massSun2 * massSun3)/(length2_3) * (length2_3);
    float force3_2 = (bigG * massSun3 * massSun2)/(length3_2) * (length3_2);
    float force2_1 = (bigG * massSun2 * massSun1)/(length2_1) * (length2_1);
    float force3_1 = (bigG * massSun3 * massSun1)/(length3_1) * (length3_1);


    //vector forces with positive and negative values,
    sf::Vector2f vectorForce1_2 = force1_2 * normalized1_2;
    sf::Vector2f vectorForce1_3 = force1_3 * normalized1_3;

    sf::Vector2f vectorForce2_1 = force2_1 * normalized2_1;
    sf::Vector2f vectorForce2_3 = force2_3 * normalized2_3;

    sf::Vector2f vectorForce3_1 = force3_1 * normalized3_1;
    sf::Vector2f vectorForce3_2 = force3_2 * normalized3_2;


    sf::Vector2f netForce1 = vectorForce1_2 + vectorForce1_3;
    sf::Vector2f netForce2 = vectorForce2_1 + vectorForce2_3;
    sf::Vector2f netForce3 = vectorForce3_1 + vectorForce3_2;

    sf::Vector2f acceleration1 = netForce1 / massSun1;
    sf::Vector2f acceleration2 = netForce2 / massSun2;
    sf::Vector2f acceleration3 = netForce3 / massSun3;   



    velocity1 -= acceleration1 * deltaTime;
    velocity2 -= acceleration2 * deltaTime;
    velocity3 -= acceleration3 * deltaTime;


    position1 += velocity1 * deltaTime;
    position2 += velocity2 * deltaTime;
    position3 += velocity3 * deltaTime;

    sun1.setPosition(position1);
    sun2.setPosition(position2);
    sun3.setPosition(position3);

    window.clear();
    window.draw(sun3);
    window.draw(sun2);
    window.draw(sun1);
    window.display();
    }
}