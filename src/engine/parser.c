#include <stdio.h>
#include <stdlib.h>
#include "parser.h"

inline int is_number(char *src){
	return *src>='0' && *src<='9';
}

//Reads the first integer from the source string and places it in
//  the destination int
char* read_next_int(char *src, int *dst){
	//Until a number is found
	while (!is_number(src)){
		//If the null character is found before a number
		if (*src=='\0'){
			//NULL is returned
			return NULL;
		}
		//The source pointer is incremented
		src++;
	}
	//The destination variable is set to 0
	*dst=0;
	//As long as there are numbers
	while (is_number(src)){
		//The number is added to the destination variable
		*dst *= 10;
		*dst += (int)(*src-'0');
		//The source pointer is incremented
		src++;
	}
	//The source pointer is returned
	return src;
}

//Reads the first floating point number from the source string and
//  places it in the destination float
char* read_next_float(char *src, float *dst){
	//Until a number or a dot is found
	while (!is_number(src)){
		//If the null character is found before a number
		if (*src=='\0'){
			//NULL is returned
			return NULL;
		}
		if (*src=='.'){
			break;
		}
		//The source pointer is incremented
		src++;
	}
	//The destination variable is set to 0
	*dst=0;
	int left=0, right=0;
	//If the next character is a dot
	if (*src=='.'){
		//And the next character is a number
		if (is_number(++src)){
			//The next number is read to right
			src = read_next_int(src, &right);
		}
	}
	else{
		//Otherwise, the next number is read to left
		src = read_next_int(src, &left);
		//If after that there is a dot
		if (*src=='.'){
			//And the next character is a number
			if (is_number(++src)){
				//Then the next number is read to right
				src = read_next_int(src, &right);
			}
		}
	}
	
	//left is assigned to dst (safe implicit cast)
	*dst = left;
	//a float is created and right is copyed to it
	float fright = right;
	//Right is the decimal part, therefore, as long as it is
	//  greater or equal to one should be divided by 10
	while (fright>=1){
		fright /= 10;
	}
	//the result is added to dst
	*dst += fright;
	
	//The source pointer is returned
	return src;
}

//readInputFile: reads and parses the input file. Returns a structure with all the
//	parameters required to run the simulation.
Parameters* read_input_file(char *filepath){
	int i;
	Parameters *parameters = (Parameters*)malloc(sizeof(Parameters));
	
	FILE *input = fopen(filepath, "r");
	
	//Length is retrieved
	fseek(input, 0, SEEK_END);
	int length = ftell(input);
	fseek(input, 0, SEEK_SET);
	
	//The file is read into a buffer
	char *buffer=(char*)malloc(length*sizeof(char)), *p=buffer;
	fread(buffer, sizeof(char), length, input);
	
	fclose(input);
	
	//Simulation time
	p=read_next_float(p, &parameters->simLength);
	//Storm parameters
	p = read_next_float(p, &parameters->stormMean);
	p = read_next_float(p, &parameters->storm_i);
	p = read_next_float(p, &parameters->storm_f);
	//Taxiways
	p = read_next_int(p, &parameters->numBerths);
	p = read_next_int(p, &parameters->numTaxiways);
	p = read_next_float(p, &parameters->taxiwayTravelTime);
	p = read_next_float(p, &parameters->berthingTime);
	
	//Fixed plane parameters
	//Timing parameters: arrival
	p = read_next_float(p, &parameters->fxTypeParams.arrival_i);
	p = read_next_float(p, &parameters->fxTypeParams.arrival_f);
	//Timing parameters: load
	p = read_next_float(p, &parameters->fxTypeParams.loading_i);
	p = read_next_float(p, &parameters->fxTypeParams.loading_f);
	//Cat 3 landing gear probability
	p = read_next_float(p, &parameters->fxTypeParams.cat3Prob);
	
	//Number of types of external planes
	p = read_next_int(p, &parameters->numXPlaneTypes);
	
	parameters->xPlaneTypes = (XPlaneType*)malloc(parameters->numXPlaneTypes*sizeof(XPlaneType));
	for (i=0; i<parameters->numXPlaneTypes; i++){
		//Number of planes in the set
		p = read_next_int(p, &parameters->xPlaneTypes[i].numPlanes);
		//Timing parameters: round trip
		p = read_next_float(p, &parameters->xPlaneTypes[i].RTT_i);
		p = read_next_float(p, &parameters->xPlaneTypes[i].RTT_f);
		//Timing parameters: load
		p = read_next_float(p, &parameters->xPlaneTypes[i].loading_i);
		p = read_next_float(p, &parameters->xPlaneTypes[i].loading_f);
		//Cat 3 landing gear probability
		p = read_next_float(p, &parameters->xPlaneTypes[i].cat3Prob);
	}
	
	p = read_next_int(p, &parameters->update_mode);
	if (parameters->update_mode==1){
		p = read_next_float(p, &parameters->update_time);
	}
	else if (parameters->update_mode==2){
		p = read_next_int(p, &parameters->update_events);
	}
	
	free(buffer);
	
	return parameters;
}
