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

int main(int argc, char *argv[]){
	//Initialize
	int real_numThreads=0;
	assert(argc == 3);
	string filename( argv[2]);
	int threadnum = atoi(argv[1]);
	assert( 0 < threadnum );
	int linenumber =0;
	string line;
	map<string, word_info> wc;
	ifstream myfile (filename);
	vector<string> lines;

	//Read file in vector
	if (myfile.is_open())
	{
		while ( getline (myfile,line) )
		{
			linenumber++;
			lines.push_back(line);
		}
		myfile.close();
	}
	else{
		cout << "Unable to open file";
		return 0;
	}


	chrono::system_clock::time_point startTime = chrono::system_clock::now();
	omp_set_num_threads(threadnum);

int i;
string tmp_word;
map<string, word_info> wc_local;
#pragma omp parallel private(i, tmp_word)
    {
#pragma omp for private(i, tmp_word,wc_local) lastprivate(real_numThreads)
        for (int i = 0; i < linenumber; i++) {
            real_numThreads = omp_get_num_threads();
            string tmp_line = lines.at(i);
            size_t word_begin=0;
            for(size_t i=0;i < tmp_line.size();i++){
                if(isalpha(tmp_line[i])){
                    ; // nothin iterator is between the word
                }else{
                    int word_length= i - word_begin;
                    if(word_length>0){
                        tmp_word =tmp_line.substr(word_begin, word_length);
                        //cout << tmp_word << endl;
                        if (wc.count(tmp_word) <= 0){
                            word_info tmp;
                            tmp.count = 1;
                            tmp.lines.push_back(i);
                                wc_local[tmp_word] = tmp;
                        } else {
                                wc_local[tmp_word].count += 1;
                                wc_local[tmp_word].lines.push_back(i);
                        }
                    }
                    word_begin = i+1;
                }
            }
        }

#pragma omp critical
        for (auto& kv : wc_local) {
            if (wc.count(kv.first) <= 0){
                word_info tmp;
                word_info word_info_in_thread = kv.second;
                tmp.count= word_info_in_thread.count;
                tmp.lines = word_info_in_thread.lines;
                wc[kv.first] = tmp;
            }else{
                word_info word_info_in_thread = kv.second;
                wc[kv.first].count +=  word_info_in_thread.count;
                wc[kv.first].lines.insert(wc[kv.first].lines.end(), word_info_in_thread.lines.begin(), word_info_in_thread.lines.end());
            }
        }
    }
chrono::system_clock::time_point endTime = chrono::system_clock::now();
chrono::microseconds microRunTime =
        chrono::duration_cast<chrono::microseconds>(endTime - startTime);
double runTime = microRunTime.count() / 1000000.0;

    cout << std::setprecision(8) << "time " << runTime << " seconds." << endl
		 << flush;
	cout << "There were " << real_numThreads << " threads." << endl;
    cout << "there where " << wc.size() << " uniq words in this file" << endl;

    for (auto& kv : wc) {
        cout << kv.first;
        cout << "\t" << to_string(kv.second.count);
        std::stringstream ss;
        for(size_t i = 0; i < kv.second.lines.size(); ++i)
        {
          if(i != 0)
            ss << ",";
          ss << to_string(kv.second.lines[i]);
        }
        std::string s = ss.str();
        cout << "\t" << s << endl;
    }
	return 0;
}
