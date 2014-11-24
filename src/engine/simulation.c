#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ADTs/parameters.h"
#include "ADTs/berth.h"
#include "ADTs/taxiway.h"
#include "ADTs/plane.h"
#include "simlib/simlib.h"
#include "parser.h"
	 
//Events
#define EVENT_PLANE_ARRIVAL 0
#define EVENT_PLANE_AT_BERTHS 1
#define EVENT_PLANE_BERTH 2
#define EVENT_PLANE_LOADED 3
#define EVENT_PLANE_DEBERTH 4
#define EVENT_PLANE_DEPARTURE 5
#define EVENT_STORM_IN 6
#define EVENT_STORM_OUT 7
#define EVENT_SIM_END 8

//Event parameters
#define ATTR_PLANE_INDEX 3

//Queues
#define RUNWAY_QUEUE 1
#define BERTH_QUEUE 2

//Global variables suck, but still...
Parameters *params;

int storm;

berth_t **berths;
taxiway_t **taxiways;

int planes_size, num_x_planes;
plane_t **planes;
plane_t *fx_stat;

void enqueue(int);
void dequeue(int);
void departure(void);
void add_event(int, float);
void facilities_status(void);
void queues_status(void);

/*******************************************************************************
 * Zeroes the simulation parameters, populates queues, creates initial events. *
 *******************************************************************************/
void initialisation(){
	int i, j, index;
	
	srand(time(NULL));
	
	storm=0;
	
	//List init
	berths = (berth_t**)malloc(params->numBerths*sizeof(berth_t*));
	for (i=0; i<params->numBerths; i++){
		berths[i]=get_berth();
	}
	taxiways = (taxiway_t**)malloc(params->numTaxiways*sizeof(taxiway_t*));
	for (i=0; i<params->numTaxiways; i++){
		taxiways[i]=get_taxiway();
	}
	
	for (i=0, num_x_planes=0; i<params->numXPlaneTypes; i++){
		num_x_planes+=params->xPlaneTypes[i].numPlanes;
	}
	planes_size=num_x_planes+5;
	
	planes = (plane_t**)malloc(planes_size*sizeof(plane_t*));
	
	//End of simulation scheduling
	add_event(EVENT_SIM_END, params->simLength);
	
	//External planes start all in the runway queue
	for (i=0, index=0; i<params->numXPlaneTypes; i++){
		for (j=0; j<params->xPlaneTypes[i].numPlanes; j++, index++){
			planes[index]=get_plane(i, rand()%100<params->xPlaneTypes[i].cat3Prob);
			plane_arrival(planes[index]);
			plane_land(planes[index], sim_time);
			transfer[ATTR_PLANE_INDEX]=index;
			enqueue(RUNWAY_QUEUE);
		}
	}
	
	//Dequeue planes to get the thing started.
	dequeue(RUNWAY_QUEUE);
	
	//Fixed plane event scheduling
	transfer[ATTR_PLANE_INDEX]=index;
	planes[index]=get_plane(-1, rand()%100<params->fxTypeParams.cat3Prob);
	add_event(EVENT_PLANE_ARRIVAL, uniform(params->fxTypeParams.arrival_i, params->fxTypeParams.arrival_f, 0));
	
	//Statistics holder for fixed planes.
	fx_stat=get_plane(-1, 0);
	
	//The reminder of the array is filled with placeholders
	for (++index; index<planes_size; index++){
		planes[index]=NULL;
	}
	
	//First storm
	float time = expon(params->stormMean, 1);
	add_event(EVENT_STORM_IN, time);
	add_event(EVENT_STORM_OUT, uniform(time+params->storm_i, time+params->storm_f, 0));
}

void increment_planes_size(int increment){
	int i=planes_size;
	planes_size+=increment;
	planes=(plane_t**)realloc(planes, planes_size*sizeof(plane_t*));
	//If the operation was unsuccessful, terminate
	if (planes==NULL){
		exit(1);
	}
	//The newly allocated section of the array is filled with placeholders
	while(i<planes_size){
		planes[i++]=NULL;
	}
	printf("New 'planes' size: %d\n", planes_size);
}

void deallocation(){
	int i;
	for (i=0; i<params->numBerths; i++){
		deallocate_berth(berths[i]);
	}
	free(berths);
	for (i=0; i<params->numTaxiways; i++){
		deallocate_taxiway(taxiways[i]);
	}
	free(taxiways);
	for (i=0; i<planes_size; i++){
		if (planes[i]!=NULL){
			free(planes[i]);
		}
	}
	free(planes);
}

/******************************
 * Event insertion functions. *
 ******************************/
void add_event(int type, float time){
	printf("Added event %d at %.2f, t3: %.2f\n", type, time+sim_time, transfer[3]);
	event_schedule(sim_time+time, type);
}

/*******************************
 * Berth management functions. *
 *******************************/
int available_berth(){
	int i;
	for (i=0; i<params->numBerths; i++){
		if (is_berth_empty(berths[i])){
			return i;
		}
	}
	return -1;
}

void use_berth(int berth){
	occupy_berth(berths[berth], sim_time);
}

void empty_berth(int berth){
	free_berth(berths[berth], sim_time);
}

/*********************************
 * Taxiway management functions. *
 *********************************/
int available_taxiway(){
	int i;
	for (i=0; i<params->numTaxiways; i++){
		if (is_taxiway_empty(taxiways[i])){
			return i;
		}
	}
	return -1;
}

void use_taxiway(int taxiway){
	occupy_taxiway(taxiways[taxiway], sim_time);
}

void empty_taxiway(int taxiway){
	free_taxiway(taxiways[taxiway], sim_time);
}

/************************************
 * Queuing and dequeuing functions. *
 ************************************/
void enqueue(int queue){
	if (queue==RUNWAY_QUEUE){
		plane_enqueue(planes[(int)transfer[ATTR_PLANE_INDEX]], sim_time);
		list_file(LAST, RUNWAY_QUEUE);
	}
	else if (queue==BERTH_QUEUE){
		plane_enqueue(planes[(int)transfer[ATTR_PLANE_INDEX]], sim_time);
		list_file(LAST, BERTH_QUEUE);
	}
}

void dequeue(int queue){
	int taxiway;
	if (queue==RUNWAY_QUEUE){
		//The berth only needs to be reserved is the plane is in the runway queue
		int berth;
		while ((berth=available_berth())!=-1 && (taxiway=available_taxiway())!=-1 && list_size[RUNWAY_QUEUE]){
			//First item is dequeued
			list_remove(FIRST, RUNWAY_QUEUE);
			
			//Berth and taxiway are reserved
			reserve_berth(berths[berth], sim_time);
			use_taxiway(taxiway);
			//Plane berth and taxiway usage
			planes[(int)transfer[ATTR_PLANE_INDEX]]->berth=berth;
			planes[(int)transfer[ATTR_PLANE_INDEX]]->taxiway=taxiway;
			
			//The event is submitted
			add_event(EVENT_PLANE_AT_BERTHS, params->taxiwayTravelTime);
		}
	}
	else if (queue==BERTH_QUEUE){
		while ((taxiway=available_taxiway())!=-1 && list_size[BERTH_QUEUE]){
			//First item is dequeued
			list_remove(FIRST, BERTH_QUEUE);
			
			//Taxiway is reserved and plane usage set
			use_taxiway(taxiway);
			planes[(int)transfer[ATTR_PLANE_INDEX]]->taxiway=taxiway;
			
			//The event is submitted
			add_event(EVENT_PLANE_DEPARTURE, params->taxiwayTravelTime);
		}
	}
}

/*****************************
 * Event handling functions. *
 *****************************/
void arrival(void){
	int i, index=transfer[ATTR_PLANE_INDEX];
	
	//If the plane is a fixed plane
	if (planes[index]->set==-1){
		//The next arrival event needs to be set
		//An available index needs to be found
		for (i=num_x_planes; i<planes_size; i++){
			if (planes[i]==NULL){
				break;
			}
		}
		//If there are no indices available
		if (i==planes_size){
			//A new chunk is allocated to hold the new arrival
			increment_planes_size(5);
		}
		planes[i]=get_plane(-1, rand()%100<params->fxTypeParams.cat3Prob);
		//A new arrival event is scheduled
		transfer[ATTR_PLANE_INDEX]=i;
		add_event(EVENT_PLANE_ARRIVAL, uniform(params->fxTypeParams.arrival_i, params->fxTypeParams.arrival_f, 0));
		//The transfer array index needs to be restored
		transfer[ATTR_PLANE_INDEX]=index;
	}
	
	//Arrival is called
	plane_arrival(planes[index]);
	//If the weather is clear or the plane has cat3 landing gear
	if (!storm || planes[index]->cat3){
		//The plane can land
		plane_land(planes[index], sim_time);
		enqueue(RUNWAY_QUEUE);
	}
	else{
		//If not, the plane departs
		departure();
	}
}

void at_berths(void){
	printf("Get here, index: %d, berth: %d\n", (int)transfer[ATTR_PLANE_INDEX], planes[(int)transfer[ATTR_PLANE_INDEX]]->berth);
	use_berth(planes[(int)transfer[ATTR_PLANE_INDEX]]->berth);
	//printf("Get here\n");
	empty_taxiway(planes[(int)transfer[ATTR_PLANE_INDEX]]->taxiway);
	//printf("Get here\n");
	add_event(EVENT_PLANE_BERTH, params->berthingTime);
	//printf("Get here\n");
}

void berth(void){
	int index=transfer[ATTR_PLANE_INDEX];
	if (planes[index]->set==-1){
		add_event(EVENT_PLANE_LOADED, uniform(params->fxTypeParams.loading_i, params->fxTypeParams.loading_f, 0));
	}
	else{
		int set=planes[index]->set;
		float time = uniform(params->xPlaneTypes[set].loading_i, params->xPlaneTypes[set].loading_f, 0);
		add_event(EVENT_PLANE_LOADED, time);
	}
}

void loaded(void){
	add_event(EVENT_PLANE_DEBERTH, params->berthingTime);
}

void deberth(void){
	empty_berth(planes[(int)transfer[ATTR_PLANE_INDEX]]->berth);
	enqueue(BERTH_QUEUE);
}

void departure(void){
	int index=transfer[ATTR_PLANE_INDEX];
	int set=planes[index]->set;
	empty_taxiway(planes[index]->taxiway);
	if (set==-1){
		//Relevant stats are recorded
		fx_stat->arrivals+=planes[index]->arrivals;
		fx_stat->times_served+=planes[index]->times_served;
		fx_stat->residence_time+=planes[index]->residence_time;
		fx_stat->queue_time+=planes[index]->queue_time;
		
		//The plane is deallocated and a placeholder is set
		deallocate_plane(planes[index]);
		planes[index]=NULL;
	}
	else{
		//The new arrival event is set to time+RTT
		add_event(EVENT_PLANE_ARRIVAL, uniform(params->xPlaneTypes[set].RTT_i, params->xPlaneTypes[set].RTT_f, 0));
	}
}

int start_simulation(Parameters *p){
	int i, j;
	params=p;
	
	maxatr=4;
	init_simlib();
	initialisation();
	
	do{
		//while(1){
			timing();
			//printf("event: %d, time: %.2f\n", next_event_type, sim_time);
		//}
		
		switch (next_event_type){
			case EVENT_PLANE_ARRIVAL:
				printf("Arrival event at %.2f: %d\n", sim_time, (int)transfer[ATTR_PLANE_INDEX]);
				arrival();
				break;
			case EVENT_PLANE_AT_BERTHS:
				printf("At berths event at %.2f: %d\n", sim_time, (int)transfer[ATTR_PLANE_INDEX]);
				at_berths();
				break;
			case EVENT_PLANE_BERTH:
				printf("Berth event at %.2f: %d\n", sim_time, (int)transfer[ATTR_PLANE_INDEX]);
				berth();
				break;
			case EVENT_PLANE_LOADED:
				printf("Load complete event at %.2f: %d\n", sim_time, (int)transfer[ATTR_PLANE_INDEX]);
				loaded();
				break;
			case EVENT_PLANE_DEBERTH:
				printf("Deberth event at %.2f: %d\n", sim_time, (int)transfer[ATTR_PLANE_INDEX]);
				deberth();
				break;
			case EVENT_PLANE_DEPARTURE:
				printf("Departure event at %.2f: %d\n", sim_time, (int)transfer[ATTR_PLANE_INDEX]);
				departure();
				break;
			case EVENT_STORM_IN:
				printf("Storm in event at t=%.2f\n", sim_time);
				//Storm in
				storm++;
				//Add a new "storm in" event
				float time = expon(params->stormMean, 1);
				printf("Next storm in %.2f\n", time);
				add_event(EVENT_STORM_IN, time);
				//Add a new "storm out" event
				add_event(EVENT_STORM_OUT, uniform(time+params->storm_i, time+params->storm_f, 0));
				break;
			case EVENT_STORM_OUT:
				printf("Storm out event at t=%.2f\n", sim_time);
				//Storm out
				storm--;
				break;
		}
		
		queues_status();
		
		//Berth and taxiway availability are checked to see if something can be dequeued
		dequeue(BERTH_QUEUE);
		dequeue(RUNWAY_QUEUE);
		
		facilities_status();
	}
	while (next_event_type!=EVENT_SIM_END);
	
	//Write to file.
	
	deallocation();
	
	return 0;
}

void facilities_status(void){
	int i, j;
	for (i=0, j=0; i<params->numBerths; i++){
		if (!is_berth_empty(berths[i])){
			j++;
		}
	}
	printf("Berths in use %d/%d, ", j, i);
	for (i=0, j=0; i<params->numTaxiways; i++){
		if (!is_taxiway_empty(taxiways[i])){
			j++;
		}
	}
	printf("Taxiways in use %d/%d\n\n", j, i);
}

void queues_status(void){
	printf("Runway queue: %d, ", list_size[RUNWAY_QUEUE]);
	printf("Berth queue: %d\n", list_size[BERTH_QUEUE]);
}