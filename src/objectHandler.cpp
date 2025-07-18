#include "objectHandler.hpp"
#include "massObject.hpp"
#include "supportingFiles/functions.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>


objectHandler::objectHandler(){
    std::cout << "Hello world" << std::endl;
}


void objectHandler::add_mass(massObject mass){
    vector_of_masses.push_back(mass);
}

//must compute and store all distances, 2 for every 2 planets, m1 - m2, m2 - m1
void objectHandler::compute_distances(){
    //for m masses the first m-1 correspond to the first mass and so on so forth.
    for(size_t i = 0; i <vector_of_masses.size(); i++)
    {
        for(size_t j = 0; j < vector_of_masses.size(); j++)
        {
            if(i == j) continue;
            //generates all the values from the first object to the others,
            //second object to the others
            //third and so on so forth.
            distances.push_back(vector_of_masses[i].getPosition() - vector_of_masses[j].getPosition());
        }
    }
}

//must use the distance function
void objectHandler::compute_lengths()
{
    for (size_t i = 0; i < vector_of_masses.size(); i++)
    {
        for(size_t j = 0; j < vector_of_masses.size(); j++){
            if(i == j) continue;
            //according to the distance function, must put the 
            euclid_distances.push_back(distance(vector_of_masses[i].getPosition(), vector_of_masses[j].getPosition()));
        }
    }
}

void objectHandler::compute_normalized_vectors()
{
    for(size_t i = 0; i < distances.size(); i++)
    {
        normalized_distances_vector.push_back(normalize(distances[i]));
    }
}

//forces are the mass of the both object multiplied 
void objectHandler::compute_allForces()
{
    for(size_t i = 0; i < vector_of_masses.size(); i++)
    {
        for(size_t j = 0; j < vector_of_masses.size(); j++)
        {
            if(i==j) continue;
            int counter = 0;
            allForces.push_back((6.673e3 * vector_of_masses[i].getMass() * vector_of_masses[j].getMass()) / 
                                                    euclid_distances[counter] * euclid_distances[counter]);
            counter+=1;
        }
    }
}


//multiplying all forces by the normalized vectors
void objectHandler::compute_vectorForces()
{
    for(size_t i = 0; i < distances.size(); i++){
        vectorForces.push_back(allForces[i] * normalized_distances_vector[i]);
    }
}


//performs the addition of each vector force
void objectHandler::compute_netForce()
{
    for (size_t i = 0; i < vectorForces.size(); i += vector_of_masses.size() - 1)
    {
        sf::Vector2f netF = {0.f, 0.f};
        for (size_t j = i; j < i + vector_of_masses.size() - 1;)
        {
            netF += vectorForces[j];
        }
        netForces.push_back(netF);
        netF = {0.f, 0.f};
    }
}


void objectHandler::compute_acceleration()
{
    for(size_t i = 0; i < netForces.size(); i++)
    {
        accelerations.push_back(netForces[i]/vector_of_masses[i].getMass());
    }
}

void objectHandler::compute_velocity(float deltaTime)
{
    for (size_t i = 0; i < vector_of_masses.size(); i++)
    {
        velocities.push_back(accelerations[i] * deltaTime);
    }
}

std::vector<sf::Vector2f> objectHandler::compute_position(float deltaTime)
{
    for(size_t i = 0; i < vector_of_masses.size(); i++){
        positions.push_back(velocities[i]  * deltaTime);
    }
    return positions;
}

std::vector<sf::Vector2f> objectHandler::get_positions_vector()
{
    return this->positions;
}