#include <string>
#include <fstream>
#include <stddef.h>
#include <stdlib.h>
#include "parser.hpp"

using namespace std;

inline int isNumber(char *src){
	return *src>='0' && *src<='9';
}

//Reads the first integer from the source string and places it in
//  the destination int
char* readNextInt(char *src, int *dst){
	//Until a number is found
	while (!isNumber(src)){
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
	while (isNumber(src)){
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
char* readNextFloat(char *src, float *dst){
	//Until a number or a dot is found
	while (!isNumber(src)){
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
		if (isNumber(++src)){
			//The next number is read to right
			src = readNextInt(src, &right);
		}
	}
	else{
		//Otherwise, the next number is read to left
		src = readNextInt(src, &left);
		//If after that there is a dot
		if (*src=='.'){
			//And the next character is a number
			if (isNumber(++src)){
				//Then the next number is read to right
				src = readNextInt(src, &right);
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
Parameters* readInputFile(char *filepath){
	Parameters *parameters = (Parameters*)malloc(sizeof(Parameters));
	
	ifstream file;
	file.open(filepath);
	
	string line;
	char *cline;
	int i;
	
	//Simulation time
	getline(file, line);
	readNextFloat(const_cast<char*>(line.c_str()), &parameters->simLength);
	//Storm parameters
	getline(file, line);
	cline = const_cast<char*>(line.c_str());
	cline = readNextFloat(cline, &parameters->stormMean);
	cline = readNextFloat(cline, &parameters->storm_i);
	cline = readNextFloat(cline, &parameters->storm_f);
	//Taxiways
	getline(file, line);
	cline = const_cast<char*>(line.c_str());
	cline = readNextInt(cline, &parameters->numBerths);
	cline = readNextInt(cline, &parameters->numTaxiways);
	cline = readNextFloat(cline, &parameters->taxiwayTravelTime);
	cline = readNextFloat(cline, &parameters->berthingTime);
	
	//Fixed plane parameters
	//Timing parameters: arrival
	getline(file, line);
	cline = const_cast<char*>(line.c_str());
	cline = readNextFloat(cline, &parameters->fxTypeParams.arrival_i);
	cline = readNextFloat(cline, &parameters->fxTypeParams.arrival_f);
	//Timing parameters: load
	getline(file, line);
	cline = const_cast<char*>(line.c_str());
	cline = readNextFloat(cline, &parameters->fxTypeParams.loading_i);
	cline = readNextFloat(cline, &parameters->fxTypeParams.loading_f);
	//Cat 3 landing gear probability
	getline(file, line);
	cline = const_cast<char*>(line.c_str());
	cline = readNextFloat(cline, &parameters->fxTypeParams.cat3Prob);
	
	//Number of types of external planes
	getline(file, line);
	cline = const_cast<char*>(line.c_str());
	cline = readNextInt(cline, &parameters->numXPlaneTypes);
	
	parameters->xPlaneTypes = (XPlaneType*)malloc(parameters->numXPlaneTypes*sizeof(XPlaneType));
	for (i=0; i<parameters->numXPlaneTypes; i++){
		//Number of planes in the set
		getline(file, line);
		cline = const_cast<char*>(line.c_str());
		cline = readNextInt(cline, &parameters->xPlaneTypes[i].numPlanes);
		//Timing parameters: load
		getline(file, line);
		cline = const_cast<char*>(line.c_str());
		cline = readNextFloat(cline, &parameters->xPlaneTypes[i].loading_i);
		cline = readNextFloat(cline, &parameters->xPlaneTypes[i].loading_f);
		//Timing parameters: round trip
		getline(file, line);
		cline = const_cast<char*>(line.c_str());
		cline = readNextFloat(cline, &parameters->xPlaneTypes[i].RTT_i);
		cline = readNextFloat(cline, &parameters->xPlaneTypes[i].RTT_f);
		//Cat 3 landing gear probability
		getline(file, line);
		cline = const_cast<char*>(line.c_str());
		cline = readNextFloat(cline, &parameters->xPlaneTypes[i].cat3Prob);
	}
	
	file.close();
	
	return parameters;
}
