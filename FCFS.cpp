#include <iostream>
#include <fstream>
#include <vector>
#include "process.h"
#include "functions.h"
#include <stdlib.h>
#include <iomanip>
using namespace std;

void q_printer(vector<Process> all_p){
  if (all_p.size() == 0){
    cout << "[Q <empty>]" << endl;
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

void FCFS(vector<Process> all_p, string fname){
  int t_cs = 8;
  unsigned int total_p = all_p.size();

  int time = 0;
  int burst_end = 0;
  int burst_start = 0;
  int current_process_index = -1;
  string current_process;

  bool cpu_in_use = false;
  vector<Process> ready_q;
  vector<Process> serviced_q;

  int context_switches = 0;
  float total_turn_around_time = 0;
  float total_burst_times = 0;
  float total_wait_time = 0;

  cout << "time " << time << "ms: Simulator started for FCFS ";
  q_printer(ready_q);

  while (serviced_q.size() < total_p){
    // service the process
    if (current_process_index != -1
	&& ((!cpu_in_use && time >= burst_end) || time == t_cs*0.5)
	&& time >= all_p[current_process_index].get_blocked_until() + 4){

      context_switches++;

      cout << "time " << time << "ms: Process " << all_p[current_process_index].get_id() << " started using the CPU ";

      burst_start = time;
      burst_end = time + all_p[current_process_index].get_burst_time();

      q_printer(ready_q);

      cpu_in_use = true;
    }
    else if (time == burst_end && burst_end != 0 && cpu_in_use){

      if (!all_p[current_process_index].get_serviced()){
	total_turn_around_time += (burst_end - all_p[current_process_index].get_arrival_time());
	total_wait_time += (time - all_p[current_process_index].get_arrival_time() + 4) - all_p[current_process_index].get_burst_time();
      }
      else{
	total_turn_around_time += (burst_end - all_p[current_process_index].get_blocked_until());
	total_wait_time += (time - all_p[current_process_index].get_blocked_until() + 4) - all_p[current_process_index].get_burst_time();
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
						       all_p[current_process_index].get_io_time() + 4);
	cout << all_p[current_process_index].get_burst_count(); 
				
	if (all_p[current_process_index].get_burst_count() == 1) {
	  cout << " burst to go ";
	}
	else {
	  cout << " bursts to go ";
	}
	q_printer(ready_q);
	cout << "time " << time << "ms: Process " << all_p[current_process_index].get_id();
	cout << " switching out of CPU; will block on I/O until time ";
	cout << all_p[current_process_index].get_blocked_until() << "ms ";
	q_printer(ready_q);
      }
      else{
	all_p[current_process_index].decrease_bursts();
	all_p[current_process_index].set_blocked_until(time +
						       all_p[current_process_index].get_io_time() + 4);

	cout << "time " << time << "ms: Process " << all_p[current_process_index].get_id() << " terminated ";
	q_printer(ready_q);

	serviced_q.push_back(all_p[current_process_index]);
	all_p.erase(all_p.begin() + current_process_index);
      }
      burst_end = time + 4;
      current_process_index = -1;
    }

    for (unsigned int i=0; i<all_p.size(); i++){
      if (all_p[i].get_arrival_time() == time 
	  && all_p[i].get_blocked_until() == 0){
	//print out that a process arrived
	cout << "time " << time << "ms: Process " << all_p[i].get_id() << " arrived and added to ready queue ";

	ready_q.push_back(all_p[i]);
	q_printer(ready_q);
      }
      else if (all_p[i].get_blocked_until() == time && all_p[i].get_arrival_time() < time){
	ready_q.push_back(all_p[i]);
	cout << "time " << time << "ms: Process " << all_p[i].get_id() << " completed I/O; added to ready queue ";
	q_printer(ready_q);
      }
    }

    if(current_process_index == -1 && ready_q.size() > 0 && time >= burst_end) {
      current_process = ready_q[0].get_id();
      for (unsigned int i=0; i<all_p.size(); i++){
	if (current_process == all_p[i].get_id()){
	  current_process_index = i;
	}
      }
      ready_q.erase(ready_q.begin());
      burst_end = time + 4;
    }
    
    //go again!
    time++;
  }
  time += (t_cs/2)-1;
  
  cout << "time " << time << "ms: Simulator ended for FCFS" << endl;

  float avg_tat = (total_turn_around_time+context_switches*4) / float(context_switches);

  float avg_bt = total_burst_times / float(context_switches);

  float avg_wt = (total_wait_time - 8*context_switches) / float(context_switches);

  file_writer(avg_bt, avg_wt, avg_tat, context_switches, 0, fname, "FCFS");
}
