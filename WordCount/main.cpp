#include <iostream>
#include <omp.h>
#include <cassert>
#include <chrono>

using namespace std;

int main()
{

    int numThreads = 0;

    if ( 3 == argc )
        numThreads = string2int( argv[ 1 ] );
    else // if number of args illegal
    {
        std::cerr << "Usage: " << argv[0] << " number-of-threads" << std::endl;
        return( -1 );
    }; // end argc check

    assert( 0 < numThreads );
    assert( numThreads <= maxNumThreads );

    std::chrono::system_clock::time_point startTime = std::chrono::system_clock::now();


    omp_set_num_threads( numThreads );

    int i, linenumbers;
    /* Parsing part with openmp */

    #pragma omp parallel for                            \
        private(i) lastprivate(real_numThreads)
    for(int i=0; i < linenumbers; i++){
        /* do parsing stuff*/
    }


    std::chrono::system_clock::time_point endTime = std::chrono::system_clock::now();
    std::chrono::microseconds microRunTime
         = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    double runTime = microRunTime.count() / 1000000.0;

    std::cout << std::setprecision( 8 )
              << "time " << runTime  << " seconds."
              << std::endl << std::flush;
    std::cout << "There were " << real_numThreads << " threads." << std::endl;



}

