#include <stdio.h>
#include <stdlib.h>
#include "plane.h"

plane_t* get_plane(int set, int cat3){
	plane_t *plane=(plane_t*)malloc(sizeof(plane_t));
	
	plane->set=set;
	plane->cat3=cat3;
	
	plane->arrivals=0;
	plane->times_served=0;
	plane->residence_time=0;
	plane->queue_time=0;
	
	return plane;
}

void plane_arrival(plane_t *plane){
	plane->arrivals++;
}

void plane_land(plane_t *plane, float time){
	plane->times_served++;
	plane->in_time=time;
}

void plane_enqueue(plane_t *plane, float time){
	plane->time_queued=time;
}

void plane_dequeue(plane_t *plane, float time){
	plane->queue_time+=time-plane->time_queued;
}

void plane_takeoff(plane_t *plane, float time){
	plane->residence_time+=time-plane->in_time;
}

void deallocate_plane(plane_t *plane){
	free(plane);
}
