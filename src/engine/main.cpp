#include "ADTs/parameters.h"
#include "simlib/simlib.h"

//Events
#define EVENT_PLANE_ARRIVAL 0
#define EVENT_PLANE_IN_BERTHS 1
#define EVENT_PLANE_BERTH 2
#define EVENT_PLANE_LOADED 3
#define EVENT_PLANE_DEBERTH 4
#define EVENT_PLANE_DEPARTURE 5

#define VAR_LEN_EVENT_TYPES 6
#define FIXED_LEN_EVENT_TYPES 3 //Storm in, storm out, and sim end

//Queues
#define RUNWAY_QUEUE 1
#define BERTH_QUEUE 2

//Transfer parameters
#define PLANE_TYPE 1
#define TIME_QUEUED 2

void insert_event(int type, float time){
	event_schedule(sim_time+time, type);
}

int available_berth(Berth berths[]){
	int i;
	for (i=0; i<berths.size(); i++){
		if (berths[i].isFree()){
			return i;
		}
	}
	return -1;
}

int available_runway(Runway runways[]){
	int i;
	for (i=0; i<runways.size(); i++){
		if (runways[i].isFree()){
			return i;
		}
	}
	return -1;
}

int start_simulation(Parameters *params){
	int i, j, total_plane_types = 1+params->numXPlaneTypes;
	int num_events=VAR_LEN_EVENT_TYPES*(total_plane_types)+FIXED_LENGTH_EVENT_TYPES;
	/*
	 * Event ids are organised in such manner that allows to distinguish between planes in different sets:
	 *   -0 through total_plane_types-1 represent arrivals of each type.
	 *   -total_plane_types through 2*total_plane_types-1 represent arrival to berth.
	 *   -etc...
	 */
	int *events=(int*)malloc(num_events*sizeof(int));
	
	Berth berths[params->num_berths];
	Taxiway taxiways[param->num_taxiways];
	
	for (i=0; i<num_events; i++){
		events[i]=i;
	}
	
	init_simlib();
	maxatr=4;
	
	//End of simulation scheduling
	insert_event(VAR_LEN_EVENT_TYPES*total_plane_types+2, params->simLength);
	
	//Initial plane event scheduling
	insert_event(0, uniform(params->fxTypeParams.arrival_i, params->fxTypeParams.arrival_f, 0));
	for (i=0; i<params->numXPlaneTypes; i++){
		for (j=0; j<params->xPlaneTypes[i].num_planes; j++){
			transfer[PLANE_TYPE]=i+1;
			transfer[TIME_QUEUED]=0;
			list_file(LAST, RUNWAY_QUEUE);
		}
	}
	
	do{
		list_remove(FIRST, RUNWAY_QUEUE);
		insert_event(EVENT_PLANE_IN_BERTHS*total_plane_types+transfer[PLANE_TYPE], params->taxiwayTravelTime);
		//Do stats
		
	}while(i!=-1 && j!=-1 && list_size[RUNWAY_QUEUE]);
	
	//First storm
	insert_event(VAR_LEN_EVENT_TYPES*total_plane_types, expon(params->stormMean, 0));
	
	do{
		timing();
		
		if (next_event_type < (EVENT_PLANE_ARRIVAL+1)*total_plane_types){
		
		}
		else if (next_event_type < (EVENT_PLANE_IN_BERTHS+1)*total_plane_types){
		
		}
		else if (next_event_type < (EVENT_PLANE_BERTH+1)*total_plane_types){
		
		}
		else if (next_event_type < (EVENT_PLANE_LOADED+1)*total_plane_types){
		
		}
		else if (next_event_type < (EVENT_PLANE_DEBERTH+1)*total_plane_types){
		
		}
		else if (next_event_type < (EVENT_PLANE_DEPARTURE+1)*total_plane_types){
		
		}
		else if (next_event_type == VAR_LEN_EVENT_TYPES*total_plane_types){
			//Storm in
		}
		else if (next_event_type == VAR_LEN_EVENT_TYPES*total_plane_types+1){
			//Storm out
		}
	}
	while (next_event_type==VAR_LEN_EVENT_TYPES*total_plane_types+2);
	
	//Write to file.
	
	return 0;
}
