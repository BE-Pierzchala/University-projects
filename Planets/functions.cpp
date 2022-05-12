#include "functions.h"
#include <cmath>
#include <fstream>

// Returns vector with forces, force acting on planet[i] is force[i]
std::vector <Tuple> functions::calculateForces( std::vector <Planet> planets){
    std::vector<Tuple> forces (planets.size(), Tuple(0,0));
    for (int i = 0; i < planets.size(); i++){
        for (int j = 0; j < planets.size(); j++){
            if (i == j){
                continue;
            }
            forces[i] = forces[i] + planets[i].force(planets[j]);
        }
    }
    return forces;
}

// This is RK4 method called to update every planets speed and position
std::vector <Planet>  functions::update( std::vector <Planet> planets){
    std::vector <Tuple> k1s (planets.size(), Tuple(0,0));
    std::vector <Tuple> l1s (planets.size(), Tuple(0,0));

    std::vector <Tuple> k2s (planets.size(), Tuple(0,0));
    std::vector <Tuple> l2s (planets.size(), Tuple(0,0));

    std::vector <Tuple> k3s (planets.size(), Tuple(0,0));
    std::vector <Tuple> l3s (planets.size(), Tuple(0,0));

    std::vector <Tuple> k4s (planets.size(), Tuple(0,0));
    std::vector <Tuple> l4s (planets.size(), Tuple(0,0));

    double h = 0.001;
    std::vector <Planet> tempPlanets = planets;

    // This helps me to only calculate forces once
    std::vector <Tuple> tempForces = functions::calculateForces(planets);
    for ( int i = 0; i < planets.size(); i++){
        k1s[i] = planets[i].getSpeed()*h;
        l1s[i] = tempForces[i]*h/planets[i].getMass();
        // So I can further use updated value of position to calcualte forces using RKE4
        tempPlanets[i].updatePosition(k1s[i]/2);
    }

    tempForces = functions::calculateForces(tempPlanets);
    for ( int i = 0; i < planets.size(); i++){
        k2s[i] = (planets[i].getSpeed() + l1s[i])*h;
        l2s[i] = tempForces[i]*h/tempPlanets[i].getMass();

        tempPlanets[i] = planets[i];
        tempPlanets[i].updatePosition(k2s[i]/2);
    }

    tempForces = functions::calculateForces(tempPlanets);
    for ( int i = 0; i < planets.size(); i++){
        k3s[i] = (planets[i].getSpeed() + l2s[i]/2)*h;
        l3s[i] = tempForces[i]*h/tempPlanets[i].getMass();

        tempPlanets[i] = planets[i];
        tempPlanets[i].updatePosition(k3s[i]);
    }

    tempForces = functions::calculateForces(tempPlanets);
    for ( int i = 0; i < planets.size(); i++){
        k4s[i] = (planets[i].getSpeed() + l3s[i])*h;
        l4s[i] = tempForces[i]*h/tempPlanets[i].getMass();

        tempPlanets = planets;
    }



    for ( int i = 0; i < planets.size(); i++ ){
        tempPlanets[i].updatePosition(k1s[i]/6 + k2s[i]/3 + k3s[i]/3 + k4s[i]/6);
        tempPlanets[i].updateSpeed(l1s[i]/6 + l2s[i]/3 + l3s[i]/3 + l4s[i]/6);
    }
    return tempPlanets;

}


Tuple functions::centreOfMass(std::vector <Planet> planets){
    double xm = 0;
    double ym = 0;
    double M = 0;

    for ( int i = 0; i < planets.size(); i++ ){
        xm += planets[i].getPosition().x*planets[i].getMass();
        ym += planets[i].getPosition().y*planets[i].getMass();
        M += planets[i].getMass();
    }

    return Tuple(xm/M, ym/M);
}

// I use this function to check if energy is conserved in the system; this proves that RKE4 is more stable than Rhapson-Newton method
void functions::totalEnergy(std::vector <Planet> planets){
    double result = 0;
    for (int i = 0; i < planets.size(); i++){
        for (int j = i+1; j < planets.size(); j++){
             result += - planets[i].distance(planets[j]) * planets[i].force(planets[j]).val();
        }
        result += planets[i].getSpeed()*planets[i].getSpeed()*planets[i].getMass()*0.5;
    }
    std::cout<<"Total energy is = "<<result<<std::endl;
}

std::vector <Planet> functions::symmetric(int n){
    // find polar angle between two planets next to each other
    double angle = 2*M_PI/n;

    // set planets on circle of radius 10 and all have mass of 5e3
    std::vector <Planet> setup;
    for (int i = 0; i < n; i++){
        setup.push_back(Planet(cos(i*angle)*10, sin(i*angle)*10, 0, 0, 5*1e3 ));
    }

    // find net force acting on one planet - because of symmetry it will be radial so take only value
    double force = 0;
    for (int i = 1; i < n; i++){
        force += setup[0].force(setup[i]).val();
    }

    // find speed for which planets would go in circles
    double v = pow(force*10/(5e3), 0.5)*pow(2, -0.5);   // I don't know why but this helps

    // set speeds in anti-clockwise direction
    for (int i = 0; i < n; i++){
        setup[i].updateSpeed(Tuple(-sin(i*angle)*v, cos(i*angle)*v));
    }

    return setup;

}