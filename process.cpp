#include "process.h"

Process::Process() {
	id = "";
	arrival_time = 0;
	burst_time = 0;
	remaining_burst_time = 0;
	burst_count = 0;
	io_time = 0;
	
	turn_around_time = 0;
	wait_time = 0;

	blocked_until = 0;
	serviced = false;
}

Process::Process(string id1, int arrival_time1, int burst_time1, int burst_count1, int io_time1){
	id = id1;
	arrival_time = arrival_time1;
	burst_time = burst_time1;
	remaining_burst_time = burst_time1;
	burst_count = burst_count1;
	io_time = io_time1;

	turn_around_time = 0;
	wait_time = 0;

	blocked_until = 0;
	serviced = false;
}

string Process::get_id() const{
	return id;
}
int Process::get_arrival_time() const{
	return arrival_time;
}
int Process::get_burst_time() const{
	return burst_time;
}
int Process::get_remaining_burst_time() const{
        return remaining_burst_time;
}
int Process::get_burst_count() const{
	return burst_count;
}
int Process::get_io_time() const{
	return io_time;
}

int Process::get_turn_time() const{
	return turn_around_time;
}
int Process::get_wait_time() const{
	return wait_time;
}
int Process::get_blocked_until() const{
	return blocked_until;
}
bool Process::get_serviced() const{
	return serviced;
}


void Process::set_blocked_until(int b) {
	blocked_until = b;
}

void Process::decrease_bursts() {
	burst_count--;
}

void Process::set_serviced() {
	serviced = true;
}

void Process::set_remaining_burst_time(int b){
	remaining_burst_time = b;
}
