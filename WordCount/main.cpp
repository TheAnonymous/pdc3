#include <iostream>
#include <cassert>
#include <chrono>

#include <vector>
#include <map>
#include <fstream>
#include <string>
#include <cmath> // for fabs()
#include <iomanip>
#include <sstream>


#include <omp.h>
using namespace std;

struct word_info{
	int count;
	vector<int> lines;
} word;

int main(int argc, char *argv[])
{
	int numThreads = 0;
	int real_numThreads=0;
	assert(argc == 2);
	chrono::system_clock::time_point startTime = chrono::system_clock::now();

	string filename( argv[3], argv[3]+1);
	int threadnum = atoi(argv[2]);

	assert( 0 < threadnum );

	int linenumber =0;
	string line;
	map<string, word_info> wc;
	ifstream myfile (filename);
	if (myfile.is_open())
	{
	  while ( getline (myfile,line) )
	  {
		  linenumber++;
		//Put code here



	  }
	  myfile.close();
	}
	else{
		cout << "Unable to open file";
		return 0;
	}

	omp_set_num_threads(numThreads);

	int i, linenumbers;
	/* Parsing part with openmp */

	#pragma omp parallel for                            \
		private(i) lastprivate(real_numThreads)
	for(int i=0; i < linenumbers; i++){
		/* do parsing stuff*/
	}


	chrono::system_clock::time_point endTime = chrono::system_clock::now();
	chrono::microseconds microRunTime
		 = chrono::duration_cast<chrono::microseconds>(endTime - startTime);
	double runTime = microRunTime.count() / 1000000.0;

	cout << std::setprecision( 8 )
			  << "time " << runTime  << " seconds."
			  << endl <<flush;
	cout << "There were " << real_numThreads << " threads." << endl;

	return 0;
}

