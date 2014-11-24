#ifndef __TAXIWAY_H__
#define __TAXIWAY_H__

#include "status.h"

typedef struct taxiway_s{
	status_e status;
	float in_time, occupied_time;
}taxiway_t;

taxiway_t* get_taxiway(void);
int occupy_taxiway(taxiway_t*, float time);
int free_taxiway(taxiway_t*, float time);
int is_taxiway_empty(taxiway_t*);
void deallocate_taxiway(taxiway_t*);

#endif
