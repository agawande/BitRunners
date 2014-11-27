#include <stdlib.h>
#include "berth.h"

berth_t* get_berth(void){
	berth_t *berth = (berth_t*)malloc(sizeof(berth_t));
	
	berth->status=empty;
	berth->reserved_time=0;
	berth->occupied_time=0;
	
	return berth;
}

int reserve_berth(berth_t *berth, float time){
	if (berth->status==empty){
		berth->status=reserved;
		berth->in_time=time;
		return 1;
	}
	return 0;
}

int occupy_berth(berth_t *berth, float time){
	if (berth->status==reserved){
		berth->status=occupied;
		berth->reserved_time+=time-berth->in_time;
		berth->in_time=time;
		return 1;
	}
	return 0;
}

int free_berth(berth_t *berth, float time){
	if (berth->status==occupied){
		berth->status=empty;
		berth->occupied_time+=time-berth->in_time;
		return 1;
	}
	return 0;
}

int is_berth_occupied(berth_t *berth){
	return berth->status==occupied;
}

int is_berth_reserved(berth_t *berth){
	return berth->status==reserved;
}

int is_berth_empty(berth_t *berth){
	return berth->status==empty;
}

void deallocate_berth(berth_t *berth){
	free(berth);
}
