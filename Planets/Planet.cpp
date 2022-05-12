#include "Planet.h"
#include <iostream>
#include <cmath>

Planet::Planet(double _posX, double _posY, double _speedX,double _speedY, double _mass){
    position = Tuple(_posX, _posY);
    speed = Tuple(_speedX, _speedY);
    mass = _mass;
}
void Planet::updatePosition(Tuple new_posistion){
    position = position + new_posistion;
}

void Planet::updateSpeed(Tuple new_speed){
    speed = speed + new_speed;
}

Tuple Planet::getPosition(){
    return position;
}

Tuple Planet::getSpeed(){
    return speed;
}
double Planet::getMass(){
    return mass;
}

Tuple Planet::force(Planet planet) {
    double G = 0.5e-2;
    double distance_sqaured = (position - planet.position)*(position - planet.position);
    double c =  G * mass * planet.getMass() / pow(distance_sqaured, 1.5) ;
    return  (planet.position - position)*c;
}

void Planet::explainPlanet(){
    std::cout<<"Position x = "<<position.x<<std::endl;
    std::cout<<"Position y = "<<position.y<<std::endl;
    std::cout<<"Speed x = "<<speed.x<<std::endl;
    std::cout<<"Speed y = "<<speed.y<<std::endl;
    std::cout<<"Mass = "<<mass;
}

double Planet::distance(Planet planet){
    return pow(((position - planet.getPosition())*(position - planet.getPosition())), 0.5);
}