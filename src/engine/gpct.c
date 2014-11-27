#include <stdio.h>

#include "ADTs/parameters.h"
#include "parser.h"
#include "sim_io.h"
#include "simulation.h"

#define INPUT_FILENAME "sample_input"
#define BREAK_FILENAME "_kill"
#define SLEEP_TIME_US 500*1000

int main(void){
	while (!exists(BREAK_FILENAME)){
		if (exists(INPUT_FILENAME)){
			Parameters *params = read_input_file(INPUT_FILENAME);
			printf("Update mode set to %d", params->update_mode);
			if (params->update_mode){
				printf(" each %.2f hours.", params->update_time);
			}
			printf("\n");
			remove(INPUT_FILENAME);
			start_simulation(params);
			//free(params);
		}
		usleep(SLEEP_TIME_US);
	}
	printf("Kill requested.\n");
	remove(BREAK_FILENAME);
	return 0;
}
