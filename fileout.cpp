#include <iostream>
#include <fstream>
#include <vector>
#include "process.h"
#include "functions.h"
#include <stdlib.h>
#include <iomanip>
using namespace std;

void file_writer(float avg_bt, float avg_wt, float avg_tat, int context_switches, int preemptions, string fname, string algo){
	ofstream myfile;
	myfile.open(fname, ofstream::app);
	myfile << "Algorithm " << algo << endl;
	myfile << "-- average CPU burst time: " << setprecision(2) << fixed << avg_bt << " ms" << endl;
	myfile << "-- average wait time: " << setprecision(2) << fixed << avg_wt << " ms" << endl;
	myfile << "-- average turnaround time: " << setprecision(2) << fixed << avg_tat << " ms" << endl;
	myfile << "-- total number of context switches: " << context_switches << endl;
	myfile << "-- total number of preemptions: " << preemptions << endl;
	myfile << endl;
	myfile.close();
}
