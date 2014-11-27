#include <stdio.h>

int exists(char *filename){
	FILE *input = fopen(filename, "r");
	
	if (input!=NULL){
		fclose(input);
		return 1;
	}
	return 0;
}
