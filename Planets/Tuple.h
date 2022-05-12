#include <iostream>
#ifndef SESSION_5_TUPLE_H
#define SESSION_5_TUPLE_H


#include "Tuple.h"

class Tuple{
public:
    double x,y;
    Tuple(double x, double y);

    Tuple operator+ (Tuple c);
//    Tuple operator+= (Tuple c);
    Tuple operator- (Tuple c);
    Tuple operator* (double c);
    Tuple operator/ (double c);
    double operator* (Tuple t);

    double val();
};



#endif //SESSION_5_TUPLE_H
