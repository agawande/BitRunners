#include <stdio.h>
#include <stdlib.h>
#include "parser_test.h"

using namespace std;

int main(){
	//Int test
	//File is opened
	FILE *file = fopen("test_int", "r");
	
	//Check for NULL
	if (file == NULL){
		printf("The file does not exist.\n");
		exit(1);
	}
	
	//The length of the file is calculated
	fseek(file, 0, SEEK_END);
	int length = ftell(file);
	fseek(file, 0, SEEK_SET);
	
	//The file is read into a string
	char *buffer = (char*)malloc(length*sizeof(char));
	fread(buffer, sizeof(char), length, file);
	
	//close the file
	fclose(file);
	
	printf("String read: %s\nParsed integers:", buffer);
	
	int integer;
	char *pc = buffer;
	while ((pc = read_next_int(pc, &integer)) != NULL){
		printf(" %d", integer);
	}
	
	free(buffer);
	
	//Float test
	//File is opened
	file = fopen("test_float", "r");
	
	//Check for NULL
	if (file == NULL){
		printf("The file does not exist.\n");
		exit(1);
	}
	
	//The length of the file is calculated
	fseek(file, 0, SEEK_END);
	length = ftell(file);
	fseek(file, 0, SEEK_SET);
	
	//The file is read into a string
	buffer = (char*)malloc(length*sizeof(char));
	fread(buffer, sizeof(char), length, file);
	
	//close the file
	fclose(file);
	
	printf("\n\nString read: %s\nParsed floats:", buffer);
	
	float floatingpoint;
	pc = buffer;
	while ((pc = read_next_float(pc, &floatingpoint)) != NULL){
		printf(" %.2f", floatingpoint);
	}
	
	printf("\n\n");
	
	free(buffer);
	return 0;
}
