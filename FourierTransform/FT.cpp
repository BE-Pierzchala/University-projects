//
//  main.cpp
//  Session 3
//
//  Created by Bartlomiej Pierzchala on 23/10/2019.
//  Copyright © 2019 Bartlomiej Pierzchala. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

using namespace std;

double period = 2.0; // define period of the function

double f(double x){     //define function however it looks
    while( x < 0 ){
        x += period;
    }                       // while statements normalise x to be between 0 and period
    while (x > period) {
        x -= period;
    }
    if ( abs(x-1) < 0.1){
        return 1;
    }
    else{
        return 0;
    }
}

double start_point = 0;    // starting point, where function is defined
double end_point = start_point + period;    // end point, where function end to be defined


int main() {
    double pi = 3.14159265359;  // It's useful to have pie around
    
    int num = 100;      // how many non-zero terms are needed, either in sin or cos, I count sin(n) and cos(m) seperately

    string path(getenv("HOME"));    // get main directory
    path += "/Desktop/data.txt";    // create name for file
    ofstream data(path);    // create file data.txt at Desktop
   
    vector <double> A (1.0e+3, 0);  // cos coefficients, I asume user won't go over 10^3
    vector <double> B (1.0e+3, 0);  // sin coefficients
    
    
    double dx = 0.001;      //define step size for integration and creating space
    
    double x = start_point; // initiate x at starting point
    int counter = 0;        // I was to lazy to create for loop, while loop makes sure that the whole range is covered
    vector <double> xs (period/dx, 0);     // range of valid xs
    vector <double> ys (period/dx, 0);    // values of f(x)
    
//    declare xs and ys basically
    while(x < end_point){
        xs[counter] = x;
        ys[counter] = f(x);
        x += dx;
        counter++;
        data << x <<" "<< f(x) <<"\n"; // original function
    }
    
    double coefficient = 2*pi/period;
    int A_count = 0;        // How many non-zero As do I have
    int B_count = 0;        // How many non-zero Bs do I have
    
    int last_element = 0; // So I know furhter down the line, at which position last calculated coefficient A/B was calculated in its vector
    
    for ( int i = 0; i < 1.0e+3; i++){      // i such that it can reach end of A/B if requirement of enough coefficents wasnt met
        for( int j = 0; j < xs.size(); j++ ){
            x = xs[j];              // just to make it cleaner
            A[i] += ys[j]*cos( i*coefficient*x)*dx;     // integrate cos coefficient
            B[i] += ys[j]*sin( i*coefficient*x)*dx;     // integrate sin coefficient
        }
        
        A[i] = 2*A[i]/period;       //from definition of fourier series
        B[i] = 2*B[i]/period;
        
        if(abs(A[i]) < 1.0e-12){        // approximate term by 0 if its really small
            A[i] = 0;
        }
        else{
            A_count ++;                         //increment counter of As
            cout<<"A"<<i<<" = "<<A[i]<<endl;    // print value of each non-zero coefficient
        }
        if(abs(B[i]) < 1.0e-12){        // approximate term by 0 if its really small
            B[i] = 0;
        }
        else{
            B_count ++;                         //increment counter of Bs
            cout<<"B"<<i<<" = "<<B[i]<<endl;    // print value of each non-zero coefficient
        }
        last_element = i;                       // as defined in line 72
        if (A_count == num || B_count == num){      //break if enough coefficient are calculated
            break;
        }
    }
    
    A[0] = A[0]/2;  //from definition of fourier series
    
    vector<double>  fourier (period/dx, 0);                 // calculate how fourier series looks like
    
    data <<"#x      f(x)        fourier(x) \n"<<endl;       // so you know whats happening in the file
    
    for (int i = 0; i < xs.size(); i++){
        x = 4*xs[i] - 2*period;    // to get bigger range on plot
        
        for( int j = 0; j < last_element; j++ ){
            fourier[i] += A[j]*cos(j*coefficient*x) + B[j]*sin(j*coefficient*x);    //calculate it
        }
        
        data << x <<" "<< f(x) <<" "<< fourier[i]<<"\n"; // original function and fourier series next to each other, so it's easy to compare on one plot
    }

    
    return 0;
}
