#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>



int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
    window.setFramerateLimit(144);

    sf::CircleShape ball;
    ball.setRadius(60);
    ball.setOrigin({ball.getRadius(), ball.getRadius()});
    ball.setOutlineColor(sf::Color::Red);
    ball.setPosition({160,430});
    ball.setOutlineThickness(5);
    

    sf::RectangleShape cliff;
    cliff.setPosition({100,500});
    cliff.setOutlineColor(sf::Color::Blue);
    cliff.setOutlineThickness(5);
    cliff.setFillColor(sf::Color::Transparent);
    cliff.setSize({200,500});


    float gravity = 980.0f;
    //intial velocity
    sf::Vector2f velocity(400.0f, -700.0f);
    std::cout << "time to reach max height is: " << velocity.y / gravity << std::endl;
    float wallFriction = .2f;
    float totalTime = 0.0f;
    bool maxHeightReached = false;

    sf::Clock clock;
    while (window.isOpen())
    {

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }
        //every frame you calling this function
        //clock.restart will return the time that has passed since the last restart.
        sf::Time elapsed = clock.restart();
        float deltaTime = elapsed.asSeconds();
        totalTime += deltaTime;

        // Detect peak by checking sign change
        if (!maxHeightReached && velocity.y > 0.0f)
        {
            maxHeightReached = true;
            std::cout << "Ball reached max height at: " << totalTime << " seconds" << std::endl;
        }
        velocity.y += gravity * deltaTime;


        sf::Vector2f position = ball.getPosition();

        if (position.y + ball.getRadius() * 2 >= 1080)
        {
            velocity.y = -velocity.y * wallFriction;
        }
        position += velocity * deltaTime;

        if (position.x + ball.getRadius() + ball.getOutlineThickness() >= 1920)
        {
            position.x = 1920 - ball.getRadius() -ball.getOutlineThickness();
            velocity.x = -velocity.x * wallFriction;
        }

        ball.setPosition(position);


        window.clear();
        window.draw(ball);
        window.draw(cliff);
        window.display();
    }
}
