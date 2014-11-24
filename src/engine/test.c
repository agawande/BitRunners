#include <stdio.h>
#include <stdlib.h>

#include "simlib/simlib.h"

int main(){
	init_simlib();
	
	transfer[3]=5;
	event_schedule(4, 0);
	transfer[3]=6;
	event_schedule(5, 1);
	event_schedule(654, 6);
	event_schedule(7, 2);
	event_schedule(88, 4);
	event_schedule(9, 3);
	event_schedule(123, 5);
	
	while(1){
		timing();
		printf("Event: %d, time: %.2f, t3: %.2f\n", next_event_type, sim_time, transfer[3]);
	}
}
