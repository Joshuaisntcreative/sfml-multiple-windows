
#include "supportingFiles/Gui.hpp"
#include "massObject.hpp"
#include <random>
#include <chrono>



//random massObject
massObject::massObject()
{
    using namespace sf;
    colors = {Color::White, Color::Red, Color::Green, Color::Blue, Color::Yellow, Color::Magenta, Color::Cyan};
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);



    std::uniform_int_distribution<int> x_coordinates_generator(200, 1300);
    std::uniform_int_distribution<int>y_coordinates_generator(150, 900);

    float x_coordinate =static_cast<float>(x_coordinates_generator(generator));
    float y_coordinate =static_cast<float>(y_coordinates_generator(generator));
    this->setRadius(30.f);
    this->setPosition({x_coordinate, y_coordinate});
    this->setFillColor(sf::Color::White);
    this->setOrigin({this->getRadius(), this->getRadius()});
    this->setOutlineThickness(5.f);
    this->setOutlineColor(colors[rand() % 7]);

}

float massObject::getMass() const{
    return mass;
}