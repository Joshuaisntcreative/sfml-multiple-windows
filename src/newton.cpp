#include "newton.hpp"

void drawNewton(sf::RenderWindow& window) {
    sf::RectangleShape block(sf::Vector2f(60.f, 60.f));
    block.setFillColor(sf::Color::Red);
    block.setPosition({400, 300});
    window.draw(block);
}