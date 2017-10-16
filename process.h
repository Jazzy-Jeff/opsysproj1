#include <string>
using namespace std;

class Process{
public:
	Process();
	Process(string id1, int arrival_time1, int burst_time1, int burst_count1, int io_time1);

	//Accessors
	string get_id() const;
	int get_arrival_time() const;
	int get_burst_time() const;
<<<<<<< HEAD
	int get_remaining_burst_time() const;
=======
>>>>>>> ce4b36030526642dec0402ee3b76062eb4f976a9
	int get_burst_count() const;
	int get_io_time() const;
	int get_turn_time() const;
	int get_wait_time() const;
	int get_blocked_until() const;
	bool get_serviced() const;

	//Modifiers
	void set_blocked_until(int b);
	void decrease_bursts();
	void set_serviced();
<<<<<<< HEAD
	void set_remaining_burst_time(int b);
=======
>>>>>>> ce4b36030526642dec0402ee3b76062eb4f976a9

private:
	string id;
	int arrival_time;
	int burst_time;
<<<<<<< HEAD
	int remaining_burst_time;
=======
>>>>>>> ce4b36030526642dec0402ee3b76062eb4f976a9
	int burst_count;
	int io_time;

	int turn_around_time;
	int wait_time;

	int blocked_until;
	bool serviced;
<<<<<<< HEAD
};
=======
};
>>>>>>> ce4b36030526642dec0402ee3b76062eb4f976a9
