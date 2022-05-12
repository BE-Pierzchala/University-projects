// This program solves numerically 2nd order ODE's using 4th order Runge-Kutta algorithm

// command to gnuplot it:
// set title ' Simple pendulum with initial speed = 0 and initial position = 3.13 rad '; set xlabel 'time [s]'; set ylabel 'position [rad]'; set y2label 'speed [rad/s]'; plot 'data.txt' using 1:2 with lines t 'position ', 'data.txt' using 1:3 with lines t 'speed'

#include <iostream>
#include <cmath>
#include <tuple>
#include <vector>
#include <fstream>

using namespace std;

// can't figure out lambda functions in c++, so here it is...
double lambda(double time,double position,double speed){
    return speed;
}
// here define your function, in my case its a pendulum
double ODE(double time, double position, double speed){
    return -sin(position);
}

// I just copied method from internet, this is implementation, nothing exciting
tuple <double, double> RKE(double time, double position, double speed, double h){
    double k1 = h*lambda(time, position, speed);
    double l1 = h*ODE(time, position, speed);
    
    double k2 = h*lambda(time + h/2, position + k1/2, speed + l1/2);
    double l2 = h*ODE(time + h/2, position + k1/2, speed + l1/2);
    
    double k3 = h*lambda(time + h/2, position + k2/2, speed + l2/2);
    double l3 = h*ODE(time + h/2, position + k2/2, speed + l2/2);
    
    double k4 = h*lambda(time + h, position + k3, speed + l3);
    double l4 = h*ODE(time + h, position + k3, speed + l3);
    
    double next_position = position + (k1/6 + k2/3 + k3/3 + k4/6);
    double next_speed = speed + (l1/6 + l2/3 + l3/3 + l4/6);
    
    return make_tuple(next_position, next_speed);
}

int main(int argc, const char * argv[]) {
    // set initial values, h is step size
    double h = 0.01;
    double initial_position = 3.13;
    double initial_speed = 0;
    
    // initialise vectors to hold data
    vector <double> times (1.0e+6, 0);
    vector <double> positions (1.0e+6, 0);
    vector <double> speeds (1.0e+6, 0);
    
    //set initial values in the vectors
    times[0] = 0;
    positions[0] = initial_position;
    speeds[0] = initial_speed;
    
    // prepare a file to write in it
    string path(getenv("HOME"));    // get main directory
    path += "/Desktop/data.txt";    // create name for file
    ofstream data(path);            // create file data.txt at Desktop
    
    // label data and put in initial values
    data << "# time position speed \n" << endl;
    data << times[0] <<" " << positions[0] << " " <<speeds[0] << "\n";
    
    // iterate it for 30s in my case and write it into file
    for ( int i = 1; i < int(30/h); i++){
        times[i] = times[i-1] + h;
        tie(positions[i], speeds[i]) = RKE(times[i-1], positions[i-1], speeds[i-1], h);
        
        data << times[i] <<" " << positions[i] << " " <<speeds[i] << "\n";
    }
    
    data.close();
    return 0;
}




