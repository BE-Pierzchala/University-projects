
#ifndef SESSION_5_FUNCTIONS_H
#define SESSION_5_FUNCTIONS_H

#include <vector>
#include "Tuple.h"
#include "Planet.h"


namespace functions {

    // calcualtes net force acting on each planet
    std::vector <Tuple> calculateForces( std::vector <Planet> planets);

    // updates position of planet, using RKE4 with fixed step of size 0.001
    std::vector <Planet>  update( std::vector <Planet> planets);

    void totalEnergy(std::vector <Planet> planets);

    // finds centre of mass
    Tuple centreOfMass(std::vector <Planet> planets);

    // sets n planets on a circle around (0,0) so the can go in circles
    // at least they're supposed to
    std::vector <Planet> symmetric(int n);
};


#endif //SESSION_5_FUNCTIONS_H
