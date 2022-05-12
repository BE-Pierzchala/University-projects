#include "Tuple.h"
#include <cmath>

Tuple::Tuple(double _x, double _y) {
    x = _x;
    y = _y;
}
// overriding addition
Tuple Tuple::operator+ (Tuple c) {
    Tuple result = Tuple(0,0);
    result.x = this->x + c.x;
    result.y = this->y + c.y;
    return result;
}

Tuple Tuple::operator- (Tuple c) {
    Tuple result = Tuple(0,0);
    result.x = this->x - c.x;
    result.y = this->y - c.y;
    return result;
}

Tuple Tuple::operator* (double c){
    return Tuple(this->x * c, this->y * c);
}

double Tuple::operator* (Tuple c){
    return this->x * c.x + this->y * c.y;
}

Tuple Tuple::operator/ (double c){
    return Tuple(this->x / c, this->y / c);
}

double Tuple::val(){
    return pow((this->x * this->x + this->y * this->y), 0.5);
}