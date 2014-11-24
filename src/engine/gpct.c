#include <stdio.h>

#include "ADTs/parameters.h"
#include "parser.h"
#include "simulation.h"

#define FILENAME "sample_input"
#define SLEEP_TIME_US 500*1000

int sim_requested(void){
	FILE *input = fopen(FILENAME, "r");
	
	if (input!=NULL){
		fclose(input);
		return 1;
	}
	return 0;
}

int main(void){
	while(1){
		printf("Poll\n");
		if (sim_requested()){
			printf("Request!\n");
			//Parameters *params = read_input_file(FILENAME);
			remove(FILENAME);
			//start_simulation(params);
			//free(params);
		}
		usleep(SLEEP_TIME_US);
	}
}
