#include <stdio.h>
#include <string>
#include "../../engine/ADTs/parameters.h"
#include "../../engine/parser.hpp"

using namespace std;

int main(void){
	string input = "sample_input";
	Parameters *params = readInputFile(const_cast<char*>(input.c_str()));
	printf("get here\n");
	int i;
	
	printf("Sim time: %.2f\n\n", params->simLength);
	
	printf("Storm mean: %.2f\n", params->stormMean);
	printf("Storm length interval: %.2f-%.2f\n\n", params->storm_i, params->storm_f);
	
	printf("Number of berths: %d\n", params->numBerths);
	printf("Number of taxiways: %d\n", params->numTaxiways);
	printf("Taxiway travel time: %.2f\n", params->taxiwayTravelTime);
	printf("De/berthing time: %.2f\n\n", params->berthingTime);
	
	printf("Fixed plane arrival interval: %.2f-%.2f\n", params->fxTypeParams.arrival_i, params->fxTypeParams.arrival_f);
	printf("Fixed plane loading interval: %.2f-%.2f\n", params->fxTypeParams.loading_i, params->fxTypeParams.loading_f);
	printf("Fixed plane cat3 probability: %.2f\n\n", params->fxTypeParams.cat3Prob);
	
	printf("Number of external plane sets: %d\n\n", params->numXPlaneTypes);
	for (i=0; i<params->numXPlaneTypes; i++){
		printf("Set %d:\n", i);
		printf("\tNumber of planes: %d\n", params->xPlaneTypes[i].numPlanes);
		printf("\tRTT interval: %.2f-%.2f\n", params->xPlaneTypes[i].RTT_i, params->xPlaneTypes[i].RTT_f);
		printf("\tLoading interval: %.2f-%.2f\n", params->xPlaneTypes[i].loading_i, params->xPlaneTypes[i].loading_f);
		printf("\tCat3 probability: %.2f\n\n", params->xPlaneTypes[i].cat3Prob);
	}
	
	return 0;
}
