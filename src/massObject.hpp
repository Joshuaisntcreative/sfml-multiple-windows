#ifndef MASS_OBJECT_HPP
#define MASS_OBJECT_HPP
#include <vector>
#include <SFML/Graphics.hpp>

class massObject : public sf::CircleShape {

    public:
    massObject();

    float getMass() const;


    private:

    sf::CircleShape circle;

    std::vector<sf::Color> colors;
    
    float mass;
    


};

#endif
