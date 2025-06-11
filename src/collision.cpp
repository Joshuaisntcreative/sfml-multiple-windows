#include "collision.hpp"
#include <cmath>
#include <iostream>


//initialvelocity1 and 2 are just x directions for now
sf::Vector2f finalVelocityCalculator(float mass1, float mass2, sf::Vector2f velocity1, sf::Vector2f velocity2)
{
    float v1final = ((mass1 - mass2) * velocity1.x + 2 * mass2 * velocity2.x) / (mass1 + mass2);
    float v2final = ((mass2 - mass1) * velocity2.x + 2 * mass1 * velocity1.x) / (mass1 + mass2);
    return {v1final, v2final};
}
// Gradual force simulation to overcome static friction and accelerate
void drawCollision(sf::RenderWindow& window) {

    sf::RectangleShape platForm(sf::Vector2f(1545.f, 50.f));
    platForm.setFillColor(sf::Color::Transparent);
    platForm.setOutlineColor(sf::Color::Red);
    platForm.setOutlineThickness(5.f);
    platForm.setPosition({100, 800});

    sf::RectangleShape box1(sf::Vector2f(50.f, 50.f));
    box1.setFillColor(sf::Color::White);
    box1.setPosition({100, 745});
    box1.setOutlineThickness(5.f);
    box1.setOutlineColor(sf::Color::Blue);

    sf::RectangleShape box2(sf::Vector2f(50.f, 50.f));
    box2.setFillColor(sf::Color::White);
    box2.setPosition({1000, 745});
    box2.setOutlineThickness(5.f);
    box2.setOutlineColor(sf::Color::Green);



    //physics props
    float box1mass = 300.f;
    sf::Vector2f box1velocity = {50.f, 0.f};
    sf::Vector2f box1position = box1.getPosition();
    sf::Vector2f box1final_velocity = {0.f, 0.f};

    float box2mass = 700.f;
    sf::Vector2f box2velocity = {0.f, 0.f};
    sf::Vector2f box2position = box2.getPosition();
    sf::Vector2f box2final_velocity = {0.f, 0.f};


 
    sf::Vector2f momentums;
    sf::Vector2f finalVelocities;
    sf::Clock clock;

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();
        bool collisionOccured = false;

        if (box1position.x + box1.getSize().x + box1.getOutlineThickness() >= box2position.x){
            finalVelocities = finalVelocityCalculator(box1mass, box2mass, box1velocity, box2velocity);
            collisionOccured = true;
            box1final_velocity.x = finalVelocities.x;
            box2final_velocity.x = finalVelocities.y;
        }

        if (collisionOccured)
        {
            std::cout << "collision occured, velocities for m1 and m2 should be " << box1final_velocity.x << " and " << box2final_velocity.x << std::endl;
            box1position += box1final_velocity * deltaTime;
            box2position += box2final_velocity * deltaTime;

            box1velocity = box1final_velocity;
            box2velocity = box2final_velocity;
            
        } 
        box1position += box1velocity * deltaTime;
        box2position += box2velocity * deltaTime;
        
        box1.setPosition(box1position);
        box2.setPosition(box2position);

        window.clear();
        window.draw(platForm);
        window.draw(box1);
        window.draw(box2);
        window.display();
    }
}