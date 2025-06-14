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

void displayTime(sf::Clock &clock, sf::Text &text) {
    sf::Time t = clock.getElapsedTime();
    float f = t.asSeconds();
    std::string s = std::to_string(f);
    text.setString("Timer: " + s);
}


// Gradual force simulation to overcome static friction and accelerate
void drawCollision(sf::RenderWindow& window) {


    //text components
    sf::Font font;
        if (!font.openFromFile("C:\\Users\\jjthu\\Downloads\\COMPUTER SCIENCE\\NON_SCHOOL\\cmake projects\\sfml-multiple-windows\\dependencies\\ROCK.TTF")) {
        std::cerr << "Error loading font" << std::endl;
    }
    sf::Text text(font, "Hello", 20);
    text.setPosition({10, 10});


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
    float box1mass = 100.f;
    sf::Vector2f box1velocity = {150.f, 0.f};
    sf::Vector2f box1position = box1.getPosition();
    sf::Vector2f box1final_velocity = {0.f, 0.f};

    float box2mass = 700.f;
    sf::Vector2f box2velocity = {-20.f, 0.f};
    sf::Vector2f box2position = box2.getPosition();
    sf::Vector2f box2final_velocity = {0.f, 0.f};


 
    sf::Vector2f momentums;
    sf::Vector2f finalVelocities;

    //clock used for physics calculations
    sf::Clock clock;

    sf::Clock timer;


    float totalTime = 0;

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        float deltaTime = clock.restart().asSeconds();
        totalTime += deltaTime;
        bool collisionOccured = false;

        if (!collisionOccured &&  box1position.x + box1.getSize().x + box1.getOutlineThickness() >= box2position.x){
            finalVelocities = finalVelocityCalculator(box1mass, box2mass, box1velocity, box2velocity);

            collisionOccured = true;

            box1velocity.x = finalVelocities.x;
            box2velocity.x = finalVelocities.y;

            std::cout << "Collision handled once. Velocities are updated accordingly" << std::endl;
        }
        box1position += box1velocity * deltaTime;
        box2position += box2velocity * deltaTime;

        box1.setPosition(box1position);
        box2.setPosition(box2position);

        displayTime(timer, text);


        window.clear();
        window.draw(platForm);
        window.draw(box1);
        window.draw(text);
        window.draw(box2);
        window.display();
    }
}