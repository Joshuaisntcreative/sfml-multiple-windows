#pragma once
#include <vector>
#include "massObject.hpp"
#include<SFML/GRAPHICS.hpp>


class objectHandler{

    public:
    
    objectHandler();

    void add_mass(massObject mass);

    void compute_distances();

    void compute_lengths();
    
    void compute_normalized_vectors();

    void compute_allForces();

    void compute_vectorForces();

    void compute_netForce();

    void compute_acceleration();

    void compute_velocity(float deltaTime);

    std::vector<sf::Vector2f> compute_position(float deltaTime);

    std::vector<sf::Vector2f> get_positions_vector();




    private:

    std::vector<massObject> vector_of_masses;

    //all the raw distance vectors between the masses
    std::vector<sf::Vector2f> distances;

    //distances between points/ lengths between the masses
    std::vector<float> euclid_distances;

    
    //normalize the raw distance vectors, these vectors will contain the directional data
    std::vector<sf::Vector2f> normalized_distances_vector;

    //computes all the forces in the system with the universal gravitation formula, using euclid distances as the length^2
    std::vector<float> allForces;

    //multiply corresponding all forces to the normalized_distances_vector.
    std::vector<sf::Vector2f> vectorForces;

    //add each objects vectorForces and store here.
    std::vector<sf::Vector2f> netForces;

    //stores all objects accelerations
    std::vector<sf::Vector2f> accelerations;

    std::vector<sf::Vector2f> velocities;

    std::vector<sf::Vector2f> positions;
};
