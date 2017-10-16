all: project1.cpp process.cpp fileout.cpp FCFS.cpp
	g++ -Wall project1.cpp process.cpp fileout.cpp FCFS.cpp -std=c++11
