//Gui.cpp
#include "Gui.hpp"
#include <iostream>
#include "../massObject.hpp"

Gui::Gui() 
{
    shape.setPosition({50, 50});
    shape.setSize({150, 50});
    shape.setOutlineColor(sf::Color::Blue);
    shape.setOutlineThickness(5);
    shape.setFillColor(sf::Color::Transparent);

    if (!font.openFromFile("C:\\Users\\jjthu\\Downloads\\COMPUTER SCIENCE\\NON_SCHOOL\\cmake projects\\sfml-multiple-windows\\dependencies\\ROCK.TTF"))
    {
        std::cerr << "Error loading font" << std::endl;
    }
    text.emplace(font, "hello", 20);
    text->setFillColor(sf::Color::White);
    text->setPosition({shape.getPosition().x, shape.getPosition().y});
    using namespace sf;
    colors = {Color::White, Color::Red, Color::Green, Color::Blue, Color::Yellow, Color::Magenta, Color::Cyan};

    //object handler initialization
}

void Gui::update(sf::Vector2i mousePosition, sf::Mouse::Button button)
{

    std::string xpos = std::to_string(mousePosition.x);
    std::string ypos = std::to_string(mousePosition.y);

    text->setString(" add circle ");

    if (getGlobalBounds().contains({static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)}))
    {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
            text->setString("circle added");
        }
    }
}

sf::FloatRect Gui::getGlobalBounds()  {
    return shape.getGlobalBounds(); // Forward the call
}

void Gui::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(shape, states);
    target.draw(*text,states);
    for(const auto& mass:masses){
        target.draw(mass, states);
    }
}


//make it a randomizer
void Gui::addMass(){
    massObject mass = massObject();
    objHandler.add_mass(mass);
    masses.push_back(mass);
    
}


//this will call all massObject functions needed in order to compute all the values.
void Gui::handlePhysics(float deltaTime)
{
objHandler.compute_distances();

objHandler.compute_lengths();

objHandler.compute_normalized_vectors();

objHandler.compute_allForces();

objHandler.compute_vectorForces();

objHandler.compute_netForce();

objHandler.compute_acceleration();

objHandler.compute_velocity(deltaTime);

objHandler.compute_position(deltaTime); 
}


void Gui::update_positions()
{
    std::vector<sf::Vector2f> positions = objHandler.get_positions_vector();
    for(size_t i = 0; i < masses.size(); i++)
    {
        masses[i].updatePosition({positions[i]});
    }
}