#include <cmath>
#include "functions.hpp"


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


float dotProduct(const sf::Vector2f& vec1, sf::Vector2f& vec2)
{
    return vec1.x * vec2.x + vec1.y * vec2.y;
}