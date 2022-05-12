//  random walk.cpp
//  Session 1
//
//  Created by Bartlomiej Pierzchala on 16/10/2019.
//  Copyright © 2019 Bartlomiej Pierzchala. All rights reserved.
//


#include <cstdlib>
#include <iostream>
#include <ctime>
#include <cmath>
#include <vector>

using namespace std;


int random_step() {
    //generates random integer from -1,1, with same propability
    return 2* ( rand() % 2 ) - 1;
}

// Calculates distance from origin after n steps, where each one can be -1 or 1
int distance(int number_of_steps){
    int dist = 0;
    
    for ( int i = 0; i < number_of_steps - 1; i++){
        dist += random_step();
    }
    return dist;
}

int main() {
    //generate seed for random number generator
    srand( (unsigned int) time(NULL) );
    
    int n = 1.0e5;                  // number of steps
    int N = 1.0e4;                   // size of sample, N > 1 so error can be calculated
    vector <int> Distances(N, 0);   // storing space for distances
    int sum = 0;                    // initizalizing sum
    double variation = 0;           // initizalizing variation
    double pi = 3.14159;
    double expected_distance = pow( 2*n/pi, 0.5);
    // refering to http://mathworld.wolfram.com/RandomWalk1-Dimensional.html
    
    for ( int i = 0; i < N; i++ ){
        int dist = abs(distance(n));
        sum += dist;                   // Simulate N walks, sum absolute value of distance from origin
        Distances [i] = dist;          // and store value of each distance from origin to calculate error
    }                                  // later
    double average = sum/N;
    
    for ( int i =0; i < N; i++){
        variation += pow(average - Distances[i], 2);  // calculating variation
    }
    
    double error = pow(variation/(N*(N-1)), 0.5);    // as in "An introduction to error analysis" by
                                                     // John R. Taylor
    cout<<average<<" +- "<<error<<endl;
    cout<<expected_distance<<endl;                  // print results and compare with expected value
    if ( abs(average - expected_distance) < error){
        cout<<"Nice"<<endl;
    }
    else{
        cout<<"Well, better luck next time"<<endl;
    }
    return 0;
}
