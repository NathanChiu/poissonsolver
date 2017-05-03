//
// Created by nathan on 03/05/17.
//
//Compute solution to Poisson's equation assuming Dirichlet boundary condition.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <functional>

void poisson1D( void );

void poisson1D(void) {

    //Constants
    double EPS0 = 8.85418782e-12; //Permittivity of free space

//    std::cout << "Hello, World!" << std::endl;
    //Parameters
    unsigned int N = 10;           //Number of lattice points
    double sampleLength = 1e-3;   //Physical length of sample in meters
    std::vector<double> V(N,0);     //Electric potential solution to Poisson's equation (Volts)
    std::vector<double> rho(N,1.6e-12);   //Charge density, first and last are boundary conditions
    double Vold;
    double maxError = 1e-5;       //set at 1% error allowed
    double currError;
    unsigned int cycleCount = 0;
    //Setup
    rho[0] = 0;
    rho[N-1] = 10;
    std::transform( rho.begin()+1, rho.end()-1,
                    rho.begin()+1, std::bind2nd(std::divides<double>(), EPS0 ) );
    V[0] = rho[0];
    V[N-1] = rho[N-1];

    //Computation loop
    do{
        currError = 0;  //reset error for every run
        for( int i = 1; i < N-1; i++){ //for all lattice points except endpoints
            Vold = V[i];
            V[i] = (V[i-1] + V[i+1] + rho[i])/2.0; //calculate new potential
            if ( fabs((V[i] - Vold)/V[i]) > currError ){ //capture worst case error
                currError = fabs((V[i] - Vold)/V[i]);
            }
        }
        cycleCount++;
    }while( currError > maxError );

    std::cout << "Finished in " << cycleCount << " iterations." << std::endl;
    int i = 0;
    while ( i < N ){
        //std::cout << "V[" << i << "] = " << std::setprecision(20) << V[i] << "V" <<std::endl;
        std::cout << i << "," << V[i] <<std::endl;
        i++;
    }
}

//USEFUL:

//    std::cout << EPS0 << std::endl;

//    std::cout << "entering poisson" << std::endl;

//    std::cout << (rho.begin()+2)[0] << std::endl;

//    std::transform(n.begin(), n.end(), n.begin(),
//                   std::bind1st(std::multiplies<T>(),pin));

/*
    while ( i < N ){
        std::cout << rho[i] <<std::endl;
        i++;
    }
*/

//std::transform( rho.begin()+1, rho.end()-1, rho.begin()+1, std::bind2nd(std::divides<double>(), EPS0 ) );