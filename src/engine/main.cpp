#include "simlib.h"

#define EVENT_LAND 1
#define EVENT_BERTH 2
#define EVENT_DEBERTH 3
#define EVENT_TAKEOFF 4
#define EVENT_STORM_IN 5
#define EVENT_STORM_OUT 6
#define EVENT_END_SIMULATION 7

#define RUNWAY_QUEUE 1
#define BERTH_QUEUE 2

void insert(int type, float time){
	event_schedule(sim_time+time, type);
}

int main(){
	init_simlib();
}
