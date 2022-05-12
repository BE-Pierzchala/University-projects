//  random walk 2D.cpp
//  Session 2
//
//  Created by Bartlomiej Pierzchala on 16/10/2019.
//  Copyright © 2019 Bartlomiej Pierzchala. All rights reserved.
//


#include <cstdlib>
#include <iostream>
#include <ctime>
#include <cmath>
#include <vector>
#include <fstream>

using namespace std;


double random_angle() {
    //generates random angle in radians
    double pi = 3.14;
    double degrees = ( rand() % 3600 )/10; // more or less uniform distribution of angles with 1 digits after . precision
    return  degrees/360 * 2*pi; // To minimize error in value of sin/cos
}


int main() {
    srand( (unsigned int) time(NULL) );     //generate seed for random number generator
    
    int n = 1.0e4;                  // number of steps
    int N = 1.0e4;                     // number of 'walkers'
    
    string path(getenv("HOME"));    // get main directory
    path += "/Desktop/data.txt";    // create name for file
    ofstream data(path);            // create file data.txt at Desktop

    data << "# x y, x2 y2 and so on\n" << endl;     // generic header of data
    
    // initiate positions at (0,0)
    vector <double> xs (N,0);       // vector to keep current x value of each 'walker'
    vector <double> ys (N,0);       // vector to keep current y value of each 'walker'
    
    //create data
    for (int i = 0; i < n; i++){    // calculate n steps

        for(int j = 0; j < N; j++){             // for each 'walker'
            double angle = random_angle();      //create angle, at which they're going from x axis
            xs[j] += cos(angle);                // normal polar coordinates
            ys[j] += sin(angle);                // each step is 1, update position vectors
            data << xs[j] << " " << ys[j] << " ";   // write to file new position of that 'walker'
        }
        data << "\n";   // end line in data => begin to write next position
    }
    data.close();       // close data.txt file, I'm not working with it anymore
    
    
    
    string path_gnu(getenv("HOME"));
    path_gnu += "/Desktop/gnu.txt";     // same as with data, but commands for gnuplot in text file so I don't have to write it by hand
    ofstream gnu(path_gnu);
    
    string name = "'path "; // creating title for each path
    gnu << "plot 'data.txt' using 1:2 with lines t " + name +"0'";  // first walker put in by hand to avoid problems if there's only one, next ones get " , " before that line, if i put it at the end of it gnuplot would not like that
    
    // save to gnu instructions, how to plot each path, enumarting walkers so you can trace every single one on the plot, with lines connects dots. With lines.
    for(int j = 1; j < N; j++){
        gnu << ", 'data.txt' using "<< 2*j + 1 <<":" << 2*(j+1) << " with lines t " + name << j << "'";
    }
    gnu.close();
    
    // calculate sum distance from origin of all 'walkers'
    double sum = 0;
    for(int j = 0; j < N; j++){
        sum += pow( (pow(xs[j],2) + pow(ys[j],2)), 0.5);
    }
    
    double average = sum/N;

    double var = 0;
    
    for(int j = 0; j < N; j++){
        var += pow( pow( (pow(xs[j],2) + pow(ys[j],2)), 0.5) - average, 2);
    }
    
    double dev_mean = pow( var/(N*(N-1)), 0.5);
    
    cout<< average << " += " << dev_mean;
    
    
    //data file with the end points
    string path_ends(getenv("HOME"));
    path_ends += "/Desktop/ends.txt";
    ofstream ends(path_ends);
    
    for ( int i = 0; i < N; i++){
        ends << xs[i] << " " << ys[i] << "\n";
    }
    ends.close();
    
    
    return 0;
}
