#include "objectHandler.hpp"
#include "massObject.hpp"
#include "supportingFiles/functions.hpp"
#include <iostream>


objectHandler::objectHandler(){
    std::cout << "Hello world" << std::endl;
}


void objectHandler::add_mass(massObject mass){
    vector_of_masses.push_back(mass);
}

//must compute and store all distances, 2 for every 2 planets, m1 - m2, m2 - m1
void objectHandler::compute_distances(){
    for(size_t i = 0; i <vector_of_masses.size(); i++){

    }
}