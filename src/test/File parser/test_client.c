#include <stdio.h>
#include "../../engine/ADTs/parameters.h"
#include "../../engine/parser.h"

int main(void){
	Parameters *params = read_input_file("sample_input");
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
	
	printf("Mode: %d\n", params->update_mode);
	if (params->update_mode){
		printf("Time: %.2f hours\n\n", params->update_time);
	}
	
	return 0;
}
