#include "parser.hpp"

//Reads the first integer from the source string and places it in
//  the destination int
//TODO format error checking
char* readNextInt(char *src, char delimiter, int *dst){
	//Until a number is found
	while (*src<'0' || *src>'9'){
		//If the null character is found before a number
		if (*src=='\0'){
			//NULL is returned
			return NULL;
		}
		//The source pointer is incremented
		src++;
	}
	//The destination variable is set to 0
	*dst = 0;
	//Until the delimiter or null character are found
	while (*src!=delimiter && *src!='\0'){
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
//TODO format error checking
char* readNextFloat(char *src, char delimiter, float *dst){
	//Until a number is found
	while (*src<'0' || *src>'9'){
		//If the null character is found before a number
		if (*src=='\0'){
			//NULL is returned
			return NULL;
		}
		//The source pointer is incremented
		src++;
	}
	//The destination variable is set to 0
	*dst = 0;
	//Until the delimiter or null character are found
	while (*src!='.' && *src!='\0'){
		//The number is added to the destination variable
		*dst *= 10;
		*dst += (int)(*src-'0');
		//The source pointer is incremented
		src++;
	}
	int digit = 1;
	while (*src!=delimiter && *src!='\0'){
		//The number is added to the destination variable
		digit *= 10;
		*dst += (float)(*src-'0')/digit;
		//The source pointer is incremented
		src++;
	}
	//The source pointer is returned
	return src;
}

//TODO
Parameters* readInputFile(char *filepath){
	return NULL;
}
