#ifndef __PLANE_H__
#define __PLANE_H__

typedef struct plane_s{
	int set, cat3;
	int arrivals, times_served;
	int berth, taxiway;
	float in_time, residence_time;
	float time_queued, queue_time;
}plane_t;

plane_t* get_plane(int, int);
void plane_arrival(plane_t*);
void plane_land(plane_t*, float);
void plane_enqueue(plane_t*, float);
void plane_dequeue(plane_t*, float);
void plane_takeoff(plane_t*, float);
void deallocate_plane(plane_t*);

#endif
