// tension.hpp
#pragma once
#include <SFML/Graphics.hpp>
float distance(const sf::Vector2f& vec1, sf::Vector2f& vec2);
float dotProduct(const sf::Vector2f& vec1, sf::Vector2f& vec2);
sf::Vector2f normalize(const sf::Vector2f& vec);
