#ifndef __SIM_STATE_H__
#define __SIM_STATE_H__

typedef struct sim_state_s{
	int storms, storm;
	int arrivals, landings;

	berth_t **berths;
	taxiway_t **taxiways;

	int planes_size, num_x_planes;
	plane_t **planes;
	plane_t *fx_stat;
}sim_state_t;

#endif
