#ifndef __BERTH_H__
#define __BERTH_H__

#include "status.h"

typedef struct berth_s{
	status_e status;
	float in_time, reserved_time, occupied_time;
}berth_t;

berth_t* get_berth(void);
int reserve_berth(berth_t*, float time);
int occupy_berth(berth_t*, float time);
int free_berth(berth_t*, float time);
int is_berth_occupied(berth_t*);
int is_berth_reserved(berth_t*);
int is_berth_empty(berth_t*);
void deallocate_berth(berth_t*);

#endif
