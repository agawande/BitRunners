#include <stdio.h>

#include "ADTs/parameters.h"
#include "parser.h"
#include "simulation.h"

#define INPUT_FILENAME "sample_input"
#define BREAK_FILENAME "_kill"
#define SLEEP_TIME_US 500*1000

int exists(char *filename){
	FILE *input = fopen(filename, "r");
	
	if (input!=NULL){
		fclose(input);
		return 1;
	}
	return 0;
}

int main(void){
	while (!exists(BREAK_FILENAME)){
		if (exists(INPUT_FILENAME)){
			Parameters *params = read_input_file(INPUT_FILENAME);
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
