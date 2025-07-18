//Gui.hpp
#pragma once
#include <SFML/Graphics.hpp>
#include "../massObject.hpp"
#include "../objectHandler.hpp"
#include <optional>
#include <vector>

class Gui : public sf::Drawable {
public:
    Gui();

    objectHandler objHandler;

    sf::FloatRect getGlobalBounds() ;

    void update(sf::Vector2i mousePosition, sf::Mouse::Button button);

    void addMass();

    void handlePhysics(float deltaTime);

    void update_positions();


private:
    //gui class
    sf::RectangleShape shape;

    //handles events
    std::optional<sf::Event> event;
    //stores all the circles objects
    std::vector<massObject> masses;
    //stores all the colors
    std::vector<sf::Color> colors;
    sf::Font font;
    //for some magical reason you cant initialize a text object without a constructor in SFML
    std::optional<sf::Text> text;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
