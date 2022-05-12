#include <iostream>
#include <cmath>
#include "Planet.h"
#include "Tuple.h"
#include "functions.h"
#include <fstream>

int main() {

    // Initialise planets
    std::vector <Planet> planets = functions::symmetric(8);

    // prepare a file to write in it

    // ------------------------------------------------

    std::string path(getenv("HOME"));     // get main directory
    path += "/Desktop/data.txt";             // create name for file
    std::ofstream data(path);                // create file data.txt at Desktop

    data << "# gnuplot command:    ";
    data << "plot 'data.txt'  using 1:2 with lines t 'planet0'";
    for ( int i = 1; i < planets.size(); i++){
        data << ", 'data.txt' using "<<std::to_string(2*i +1)<<":"<< std::to_string(2*i +2)<<" with lines t 'planet"<<std::to_string(i)<<"'";
    }
    data << "\n";

    // label data
    data << "#";
    for ( int i = 0; i < planets.size(); i++){
        data << std::to_string(i)<<" x" <<std::to_string(i)<<", y"<<std::to_string(i);
    }
    data << "\n";

    for ( int i = 0; i < planets.size(); i++){
        data<<std::to_string(planets[i].getPosition().x)<<" "<<std::to_string(planets[i].getPosition().y)<<" ";
    }

    data<<"\n";

    // ------------------------------------------

    // Write total energy of system before simulating, so afterwards one can compare with end result and
    // see how far the system has drifted with errors, as it should be constant
    functions::totalEnergy(planets);


    // run for some time simulation. Step is 0.001s

    Tuple r0 = planets[0].getPosition();

   for( int i = 0; i < 2*192370; i++){
       planets = functions::update(planets);
       if (i % 100 == 0){
           // Write down every 100th position of planets, as points are dense
           for ( int i = 0; i < planets.size(); i++){
               data<<std::to_string(planets[i].getPosition().x)<<" "<<std::to_string(planets[i].getPosition().y)<<" ";
           }

           data<<"\n";
       }

       // if first one returns close to its starting point then break
       // as for symmetric case it will be the same as it was before
       if ( i > 100 && (planets[0].getPosition() - r0).val() < 0.01 ){
            std::cout<<i<<std::endl;
            break;
        }

    }

   // Print end value of energy of the system, to compare with previous one
    functions::totalEnergy(planets);

    data.close();
    return 0;
}
