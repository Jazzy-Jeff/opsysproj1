#include <iostream>
#include <fstream>
#include <vector>
#include "process.h"
#include "functions.h"
#include <stdlib.h>
using namespace std;

void q_printer1(vector<Process> all_p){
	if (all_p.size() == 0){
<<<<<<< HEAD
		cout << "[Q <empty>]" << endl;
=======
		cout << "[Q empty]" << endl;
>>>>>>> ce4b36030526642dec0402ee3b76062eb4f976a9
		return;
	}
	string q_art;
	q_art += "[Q ";
	for (unsigned int i=0; i<all_p.size(); i++){
		q_art += all_p[i].get_id();
		q_art += " ";
	}
	q_art.pop_back();
	q_art += "]";
	cout << q_art << endl;
}

<<<<<<< HEAD
void SRT(vector<Process> all_p, string fname){
=======
void SJF(vector<Process> all_p, string fname){
>>>>>>> ce4b36030526642dec0402ee3b76062eb4f976a9
	int t_cs = 8;
	unsigned int total_p = all_p.size();

	int time = 0;
	int burst_end = 0;
	int burst_start = 0;
	int current_process_index = 0;
	string current_process;

	bool cpu_in_use = false;
	vector<Process> ready_q;
	vector<Process> serviced_q;

	int context_switches = 0;
	float total_turn_around_time = 0;
	float total_burst_times = 0;
	float total_wait_time = 0;

<<<<<<< HEAD
	int preemptions = 0;

	cout << "time " << time << "ms: Simulator started for SRT ";
=======
	cout << "time " << time << "ms: Simulator started for SJF ";
>>>>>>> ce4b36030526642dec0402ee3b76062eb4f976a9
	q_printer1(ready_q);

	while (serviced_q.size() < total_p){
		for (unsigned int i=0; i<all_p.size(); i++){

			if (all_p[i].get_arrival_time() == time
				&& all_p[i].get_blocked_until() == 0){
<<<<<<< HEAD
				//check if the burst time of the process that just arrived is less than the remanining time of the process
				//currently using the CPU
				if (burst_end - time > all_p[i].get_burst_time()){
					cout << "time: " << time << "ms: Process " << all_p[i].get_id() << " arrived and will preempt ";
					cout << all_p[current_process_index].get_id() << " ";
					
					current_process_index = i;
					preemptions++;
				}
				else{
				//print out that a process arrived
				cout << "time " << time << "ms: Process " << all_p[i].get_id() << " arrived and added to ready queue ";
=======
				//print out that a process arrived
				cout << "time " << time << "ms: Process " << all_p[i].get_id() << " arrived ";
>>>>>>> ce4b36030526642dec0402ee3b76062eb4f976a9

				if( !ready_q.empty() ) {
					unsigned int j;
					for(j=0; j<ready_q.size();j++) {
						if( all_p[i].get_burst_time() < ready_q[j].get_burst_time() ) {
							ready_q.insert(ready_q.begin() + j, all_p[i]);
							break;
						}
					}
					if(j==ready_q.size()) {
						ready_q.push_back(all_p[i]);
					}
				}
				else {
					ready_q.push_back(all_p[i]);
				}
<<<<<<< HEAD
				}
=======
>>>>>>> ce4b36030526642dec0402ee3b76062eb4f976a9
				//ready_q.push_back(all_p[i]);
				q_printer1(ready_q);
			}
			else if (all_p[i].get_blocked_until() == time && all_p[i].get_arrival_time() < time){
				if( !ready_q.empty() ) {
					unsigned int j;
					for(j=0; j<ready_q.size();j++) {
						if( all_p[i].get_burst_time() < ready_q[j].get_burst_time() ) {
							ready_q.insert(ready_q.begin() + j, all_p[i]);
							break;
						}
					}
					if(j==ready_q.size()) {
						ready_q.push_back(all_p[i]);
					}
				}
				else {
					ready_q.push_back(all_p[i]);
				}
				cout << "time " << time << "ms: Process " << all_p[i].get_id() << " completed I/O ";
				q_printer1(ready_q);
			}
		}

		// service the process
		if (ready_q.size() > 0
<<<<<<< HEAD
			&& ((/*!cpu_in_use &&*/ time >= burst_end + 8) || time == t_cs*0.5)
=======
			&& ((!cpu_in_use && time >= burst_end + 8) || time == t_cs*0.5)
>>>>>>> ce4b36030526642dec0402ee3b76062eb4f976a9
			&& time >= ready_q[0].get_blocked_until() + 4){

			current_process = ready_q[0].get_id();
			context_switches++;

			for (unsigned int i=0; i<all_p.size(); i++){
				if (current_process == all_p[i].get_id()){
					current_process_index = i;
				}
			}

			cout << "time " << time << "ms: Process " << ready_q[0].get_id() << " started using the CPU ";

			burst_start = time;
			burst_end = time + ready_q[0].get_burst_time();

			ready_q.erase(ready_q.begin());
			q_printer1(ready_q);

			cpu_in_use = true;
		}
		else if (time == burst_end && burst_end != 0){

			if (!all_p[current_process_index].get_serviced()){
				total_turn_around_time += (burst_end - all_p[current_process_index].get_arrival_time());
			}
			else{
				total_turn_around_time += (burst_end - all_p[current_process_index].get_blocked_until());
			}
			total_burst_times += (burst_end - burst_start);

			cpu_in_use = false;
			all_p[current_process_index].set_serviced();
			//decrease the burst count
			//if burst count > 0 throw back in q and update blocked until
			//else put it in the serviced q and remove from all_p
			if (all_p[current_process_index].get_burst_count() > 1){
				cout << "time " << time << "ms: Process " << all_p[current_process_index].get_id() << " completed a CPU burst; ";
				all_p[current_process_index].decrease_bursts();

				all_p[current_process_index].set_blocked_until(time +
					all_p[current_process_index].get_io_time());
<<<<<<< HEAD
				if (all_p[current_process_index].get_burst_count() == 1){
					cout << all_p[current_process_index].get_burst_count() << " burst to go ";
				}
				else {
					cout << all_p[current_process_index].get_burst_count() << " bursts to go ";
				}
=======
				cout << all_p[current_process_index].get_burst_count() << " to go ";
>>>>>>> ce4b36030526642dec0402ee3b76062eb4f976a9
				q_printer1(ready_q);
				cout << "time " << time << "ms: Process " << all_p[current_process_index].get_id() << " blocked on I/O until time ";
				cout << all_p[current_process_index].get_blocked_until() << "ms ";
				q_printer1(ready_q);
			}
			else{
				all_p[current_process_index].decrease_bursts();
				all_p[current_process_index].set_blocked_until(time +
					all_p[current_process_index].get_io_time());

				cout << "time " << time << "ms: Process " << all_p[current_process_index].get_id() << " terminated ";
				q_printer1(ready_q);

				serviced_q.push_back(all_p[current_process_index]);
				all_p.erase(all_p.begin() + current_process_index);
			}
		}

		if (ready_q.size() > 0 && cpu_in_use){
			total_wait_time += ready_q.size();
		}
		else if (ready_q.size() && !cpu_in_use){
			total_wait_time += (ready_q.size()-1);
		}
		//go again!
		time++;
	}
	time += (t_cs/2)-1;
<<<<<<< HEAD
	cout << "time " << time << "ms: Simulator ended for SRT" << endl;
=======
	cout << "time " << time << "ms: Simulator ended for SJF" << endl;
>>>>>>> ce4b36030526642dec0402ee3b76062eb4f976a9

	float avg_tat = total_turn_around_time / float(context_switches);

	float avg_bt = total_burst_times / float(context_switches);

	float avg_wt = total_wait_time / float(context_switches);

<<<<<<< HEAD
	file_writer(avg_bt, avg_wt, avg_tat, context_switches, preemptions, fname, "SJF");
=======
	file_writer(avg_bt, avg_wt, avg_tat, context_switches, 0, fname, "SJF");
>>>>>>> ce4b36030526642dec0402ee3b76062eb4f976a9
}

void RR(vector<Process> all_p, string fname){
	//int time_slice = 84;
	int preemptions = 0;
	int t_cs = 8;
	unsigned int total_p = all_p.size();

	int time = 0;
	int burst_end = 0;
	int burst_start = 0;
	int current_process_index = 0;
	string current_process;

	bool cpu_in_use = false;
	vector<Process> ready_q;
	vector<Process> serviced_q;

	int context_switches = 0;
	float total_turn_around_time = 0;
	float total_burst_times = 0;
	float total_wait_time = 0;

	cout << "time " << time << "ms: Simulator started for RR ";
	q_printer1(ready_q);

	while (serviced_q.size() < total_p){
		for (unsigned int i=0; i<all_p.size(); i++){

			if (all_p[i].get_arrival_time() == time
				&& all_p[i].get_blocked_until() == 0){
				//print out that a process arrived
				cout << "time " << time << "ms: Process " << all_p[i].get_id() << " arrived ";

				ready_q.push_back(all_p[i]);
				q_printer1(ready_q);
			}
			else if (all_p[i].get_blocked_until() == time && all_p[i].get_arrival_time() < time){
				ready_q.push_back(all_p[i]);
				cout << "time " << time << "ms: Process " << all_p[i].get_id() << " completed I/O ";
				q_printer1(ready_q);
			}
		}

		// service the process
		if (ready_q.size() > 0
			&& ((!cpu_in_use && time >= burst_end + 8) || time == t_cs*0.5)
			&& time >= ready_q[0].get_blocked_until() + 4){

			current_process = ready_q[0].get_id();
			context_switches++;

			for (unsigned int i=0; i<all_p.size(); i++){
				if (current_process == all_p[i].get_id()){
					current_process_index = i;
				}
			}

			cout << "time " << time << "ms: Process " << ready_q[0].get_id() << " started using the CPU ";

			burst_start = time;
			burst_end = time + ready_q[0].get_burst_time();

			ready_q.erase(ready_q.begin());
			q_printer1(ready_q);

			cpu_in_use = true;
		}
		else if (time == burst_end && burst_end != 0){

			if (!all_p[current_process_index].get_serviced()){
				total_turn_around_time += (burst_end - all_p[current_process_index].get_arrival_time());
			}
			else{
				total_turn_around_time += (burst_end - all_p[current_process_index].get_blocked_until());
			}
			total_burst_times += (burst_end - burst_start);

			cpu_in_use = false;
			all_p[current_process_index].set_serviced();
			//decrease the burst count
			//if burst count > 0 throw back in q and update blocked until
			//else put it in the serviced q and remove from all_p
			if (all_p[current_process_index].get_burst_count() > 1){
				cout << "time " << time << "ms: Process " << all_p[current_process_index].get_id() << " completed a CPU burst; ";
				all_p[current_process_index].decrease_bursts();

				all_p[current_process_index].set_blocked_until(time +
					all_p[current_process_index].get_io_time());
				cout << all_p[current_process_index].get_burst_count() << " to go ";
				q_printer1(ready_q);
				cout << "time " << time << "ms: Process " << all_p[current_process_index].get_id() << " blocked on I/O until time ";
				cout << all_p[current_process_index].get_blocked_until() << "ms ";
				q_printer1(ready_q);
			}
			else{
				all_p[current_process_index].decrease_bursts();
				all_p[current_process_index].set_blocked_until(time +
					all_p[current_process_index].get_io_time());

				cout << "time " << time << "ms: Process " << all_p[current_process_index].get_id() << " terminated ";
				q_printer1(ready_q);

				serviced_q.push_back(all_p[current_process_index]);
				all_p.erase(all_p.begin() + current_process_index);
			}
		}

		if (ready_q.size() > 0 && cpu_in_use){
			total_wait_time += ready_q.size();
		}
		else if (ready_q.size() && !cpu_in_use){
			total_wait_time += (ready_q.size()-1);
		}
		//go again!
		time++;
	}
	time += (t_cs/2)-1;
	cout << "time " << time << "ms: Simulator ended for RR" << endl;

	float avg_tat = total_turn_around_time / float(context_switches);

	float avg_bt = total_burst_times / float(context_switches);

	float avg_wt = total_wait_time / float(context_switches);

	file_writer(avg_bt, avg_wt, avg_tat, context_switches, preemptions, fname, "RR");
}

int main(int argc, char * argv[]){

	vector<Process> all_processes;
	if( argc != 3 ) {
		fprintf(stderr, "%s %s %s\n", "Usage: ", argv[0], " <input-file> <stats-output-file>");
		return 1;
	}
	ifstream input(argv[1]);
	string buffer = "";
	string process_id;

	int arrival_t;
	int burst_t;
	int num_bursts;
	int io_time;

	int i=0;
	char holder;

	string fname = argv[2];

	while (input >> holder){
		if (holder == '#'){
			while (input.peek() != '\n'){
				if (input.eof()){break;}
				input >> holder;
			}
			continue;
		}
		if (holder != '|'){
			buffer += holder;
		}
		else{

			if (i == 0){
				process_id = buffer;
			}
			else if (i==1){
				arrival_t = stoi(buffer);
			}
			else if (i==2){
				burst_t = stoi(buffer);
			}
			else if (i==3){
				num_bursts = stoi(buffer);
			}
			i++;

			buffer = "";
		}
		if (input.peek() == '\n'){
			i=0;
			io_time = stoi(buffer);

			Process p(process_id, arrival_t, burst_t, num_bursts, io_time);
			all_processes.push_back(p);

			buffer = "";
			input >> holder;
			buffer+=holder;
		}
	}
	//io_time = stoi(buffer);
	//Process p(process_id, arrival_t, burst_t, num_bursts, io_time);
	//all_processes.push_back(p);

	FCFS(all_processes, fname);
	cout << endl;
<<<<<<< HEAD
	SRT(all_processes, fname);
=======
	SJF(all_processes, fname);
>>>>>>> ce4b36030526642dec0402ee3b76062eb4f976a9
	cout << endl;
	RR(all_processes, fname);

	return 0;
}
