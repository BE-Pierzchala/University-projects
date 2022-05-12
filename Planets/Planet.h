#ifndef SESSION_5_PLANET_H
#define SESSION_5_PLANET_H

#include <iostream>
#include <vector>
#include "Tuple.h"


class Planet{

private:
    Tuple position = Tuple(0,0);
    Tuple speed = Tuple(0,0);
    double mass;
public:
    Planet(double _posX, double _posY, double _speedX,double _speedY, double _mass);

    void updatePosition(Tuple new_position);
    void updateSpeed(Tuple new_speed);

    Tuple getPosition();
    Tuple getSpeed();
    double getMass();

    Tuple force(Planet planet);

    double distance(Planet planet);

    // lists data about planet
    void explainPlanet();



};

#endif //SESSION_5_PLANET_H
