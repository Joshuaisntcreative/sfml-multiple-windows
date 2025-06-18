#include "newton.hpp"
#include "functions.hpp"
#include <cmath>
#include <iostream>

//m1 corresponds to the v1, for any corresponding velocities, use m3, m2 for m1
sf::Vector2f finalVelocity(float m1, float m2, sf::Vector2f u1, sf::Vector2f u2)
{
    return u1 * (m1 - m2) + 2 * m2 * u2 / (m1 + m2);
}

sf::Vector2f tangentialVelocity(sf::Vector2f tangent, sf::Vector2f velocity)
{
    return {tangent.x * velocity.x, tangent.y * velocity.y};
}


//will multiple vec1 components by vector 2
sf::Vector2f vectorMultiplier(sf::Vector2f vec1,  sf::Vector2f vec2)
{
    return {vec1.x * vec2.x, vec1.y * vec2.y};
}

// Gradual force simulation to overcome static friction and accelerate
void drawNewton(sf::RenderWindow& window) {


    sf::Font font;
        if (!font.openFromFile("C:\\Users\\jjthu\\Downloads\\COMPUTER SCIENCE\\NON_SCHOOL\\cmake projects\\sfml-multiple-windows\\dependencies\\ROCK.TTF")) {
        std::cerr << "Error loading font" << std::endl;
    }
    sf::Text text(font, "Hello", 20);
    text.setPosition({10, 10});



    sf::CircleShape m1(15.f);
    m1.setFillColor(sf::Color::White);
    m1.setPosition({800, 600});
    m1.setOutlineColor(sf::Color::Yellow);
    m1.setOutlineThickness(5.f);


    sf::CircleShape m2(15.f);
    m2.setFillColor(sf::Color::White);
    m2.setPosition({500, 600});
    m2.setOutlineColor(sf::Color::Green);
    m2.setOutlineThickness(5.f);

    const float bigG = 6.674e-2;
    float massM1 = 300.f;
    float massM2 = 3000.f;


    sf::Vector2f velocity1 = {0.f, 0.f};
    sf::Vector2f velocity2 = {0.f, 0.f};


    sf::Vector2f position1 = m1.getPosition();
    sf::Vector2f position2 = m2.getPosition();

    float combinedRadius = m1.getRadius() + m2.getRadius();
    sf::Clock clock;




    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        bool collisionOccured = false;
        float deltaTime = clock.restart().asSeconds();


        sf::Vector2f m1_2distance = m1.getPosition() - m2.getPosition();
        sf::Vector2f m2_1distance = m2.getPosition() - m1.getPosition();

        float length1_2 = distance(position2, position1);
        float length2_1 = distance(position1, position2);

    
        auto normalized1_2 = normalize(m1_2distance);
        auto normalized2_1 = normalize(m2_1distance);

        sf::Vector2f tangential1_2 = {-normalized1_2.x, normalized1_2.y};
        sf::Vector2f tangential2_1 = {-normalized2_1.x, normalized2_1.y};


        //computes the tangential velocity component on 1 from 2 and on 2 from 1 respectively.
        sf::Vector2f initialTangential1_2 = tangentialVelocity(tangential1_2, velocity1);
        sf::Vector2f initialTangential2_1 = tangentialVelocity(tangential2_1, velocity2);

        float force1_2 = (bigG * massM1 * massM2) / (length1_2) * (length1_2);
        float force2_1 = (bigG * massM2 * massM1) / (length2_1) * (length2_1);

        sf::Vector2f vectorForce1_2 = force1_2 * normalized1_2;
        sf::Vector2f vectorForce2_1 = force2_1 * normalized2_1;

        sf::Vector2f netForce1 = vectorForce1_2;
        sf::Vector2f netForce2 = vectorForce2_1;
        sf::Vector2f acceleration1 = netForce1 / massM1;
        sf::Vector2f acceleration2 = netForce2 / massM2;

        velocity1 -= acceleration1 * deltaTime;
        velocity2 -= acceleration2 * deltaTime;

        if (!collisionOccured && combinedRadius >= length1_2)
        {
            sf::Vector2f v1normal = finalVelocity(massM1, massM2, velocity1, velocity2);
            sf::Vector2f v2normal = finalVelocity(massM2, massM1, velocity2, velocity1);

            velocity1 = vectorMultiplier(v1normal, normalized1_2) + vectorMultiplier(tangential1_2, initialTangential1_2);
            velocity2 = vectorMultiplier(v2normal,normalized2_1) +vectorMultiplier(tangential2_1,initialTangential2_1);
            collisionOccured = true;
        }
        position1 += velocity1 * deltaTime;
        position2 += velocity2 * deltaTime;

        m1.setPosition(position1);
        m2.setPosition(position2);

        window.clear();
        window.draw(m1);
        window.draw(text);
        window.draw(m2);
        window.display();
    }
}