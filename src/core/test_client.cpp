#include <iostream>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "parser.hpp"

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
	
	cout << "String read:" << endl << buffer << endl << "Parsed integers:" << endl;
	
	int integer;
	char *pc = buffer;
	while ((pc = readNextInt(pc, &integer)) != NULL){
		cout << integer << endl;
	}
	
	cout << endl;
	
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
	
	cout << "String read:" << endl << buffer << endl << "Parsed floats:" << endl;
	
	float floatingpoint;
	pc = buffer;
	while ((pc = readNextFloat(pc, &floatingpoint)) != NULL){
		cout << floatingpoint << endl;
	}
	
	cout << endl;
	
	free(buffer);
	return 0;
}
