#ifndef __PARAMETERS_H__
#define __PARAMETERS_H__

/*************************************
 * A plane whose frequency is fixed. *
 *************************************/
typedef struct sFxTypeParams{
	float arrival_i, arrival_f;
	float loading_i, loading_f;
	float cat3Prob;
}FxTypeParams;

/*************************************
 * A set of planes of specific size. *
 *************************************/
typedef struct sXPlaneType{
	int numPlanes;
	float loading_i, loading_f;
	float RTT_i, RTT_f;
	float cat3Prob;
}XPlaneType;

/*******************
 * The parameters. *
 *******************/
typedef struct sParameters{
	//Duration of the simulation.
	float simLength;
	//Storm timing parameters.
	float stormMean, storm_i, storm_f;
	//Airport parameters:
	//Number of berths and taxiways.
	int numBerths, numTaxiways;
	//Time it takes to berth, deberth and travel across the taxiway.
	float taxiwayTravelTime, berthingTime;
	//Fixed plane parameters.
	FxTypeParams fxTypeParams;
	//Additional plane types:
	//Number of types of additional planes.
	int numXPlaneTypes;
	//External planes parameters.
	XPlaneType *xPlaneTypes;
	//Update parameters.
	int update_mode;
	float update_time;
	int update_events;
}Parameters;

#endif
