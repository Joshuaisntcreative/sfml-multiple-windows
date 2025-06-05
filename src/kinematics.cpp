#include "kinematics.hpp"

void drawKinematics(sf::RenderWindow& window) {
    sf::CircleShape ball(30.f);
    ball.setFillColor(sf::Color::Green);
    ball.setPosition({200, 300});
    window.draw(ball);
}