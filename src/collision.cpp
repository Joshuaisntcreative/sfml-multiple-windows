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

    sf::CircleShape mass1(50.f);
    mass1.setFillColor(sf::Color::White);
    mass1.setOrigin({mass1.getRadius(), mass1.getRadius()});
    mass1.setPosition({100, 400});
    mass1.setOutlineThickness(5.f);
    mass1.setOutlineColor(sf::Color::Blue);

    sf::CircleShape mass2(50.f);
    mass2.setFillColor(sf::Color::White);
    mass2.setOrigin({mass2.getRadius(), mass2.getRadius()});
    mass2.setPosition({700, 400});
    mass2.setOutlineThickness(5.f);
    mass2.setOutlineColor(sf::Color::Green);



    //physics props
    float mass1mass = 100.f;
    sf::Vector2f mass1velocity = {75.f, 0.f};
    sf::Vector2f mass1position = mass1.getPosition();
    sf::Vector2f mass1final_velocity = {0.f, 0.f};

    float mass2mass = 700.f;
    sf::Vector2f mass2velocity = {0.f, 0.f};
    sf::Vector2f mass2position = mass2.getPosition();
    sf::Vector2f mass2final_velocity = {0.f, 0.f};


 
    sf::Vector2f momentums;
    sf::Vector2f finalVelocities;

    float combinedRadius = mass1.getRadius() + mass2.getRadius();
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

        //x components minus y components squared 
        sf::Vector2f distanceVector = {pow(mass1position.x - mass2position.x, 2), pow(mass1position.y - mass2position.y,2)};

        float distance = sqrt(distanceVector.x + distanceVector.y);

        if(!collisionOccured && combinedRadius>= distance){
            mass1velocity = {17.68f,-17.68f};
            mass2velocity = {33.72f, 10.4f};
            collisionOccured = true;
        }
        mass1position += mass1velocity * deltaTime;
        mass2position += mass2velocity * deltaTime;

        mass1.setPosition(mass1position);
        mass2.setPosition(mass2position);

        displayTime(timer, text);


        window.clear();
        // window.draw(platForm);
        window.draw(mass1);
        window.draw(text);
        window.draw(mass2);
        window.display();
    }
}