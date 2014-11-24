#include <stdlib.h>
#include "taxiway.h"

taxiway_t* get_taxiway(void){
	taxiway_t *taxiway = (taxiway_t*)malloc(sizeof(taxiway_t));
	
	taxiway->status=empty;
	taxiway->occupied_time=0;
	
	return taxiway;
}

int occupy_taxiway(taxiway_t *taxiway, float time){
	if (taxiway->status==empty){
		taxiway->status=occupied;
		taxiway->in_time=time;
		return 1;
	}
	return 0;
}

int free_taxiway(taxiway_t *taxiway, float time){
	if (taxiway->status==occupied){
		taxiway->status=empty;
		taxiway->occupied_time+=time-taxiway->in_time;
		return 1;
	}
	return 0;
}

int is_taxiway_empty(taxiway_t *taxiway){
	return taxiway->status==empty;
}

void deallocate_taxiway(taxiway_t *taxiway){
	free(taxiway);
}
