#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <string>
using namespace std;

struct word_info{
	int count;
	vector<int> lines;
} word;

int main(int argc, char *argv[])
{
	string filename( argv[3], argv[3]+1);
	int threadnum = atoi(argv[2]);
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

	else cout << "Unable to open file";
	return 0;
}

