#ifndef __PARAMETERS_H__
#define __PARAMETERS_H__

/*************************************
 * A plane whose frequency is fixed. *
 *************************************/
typedef struct sFixedPlaneType{
	float frequency;
	float baseLoadingTime, loadingVariationTime;
}FixedPlaneType;

/*************************************
 * A set of planes of specific size. *
 *************************************/
typedef struct sExternalPlaneType{
	int numPlanes;
	float baseLoadingTime, loadingVariationTime;
	float baseRTTime, RTVariationTime;
}ExternalPlaneType;

/*******************
 * The parameters. *
 *******************/
typedef struct sParameters{
	//Duration of the simulation.
	float simLength;
	//Storm timing parameters.
	float stormMean, stormBaseTime, stormTimeVariation;
	//Taxi parameters:
	//Number of taxis.
	int numTaxi;
	//Taxi timing parameters.
	float emptyTravelTime, transportingTravelTime;
	//Fixed arrival frequency planes:
	//Frequency.
	float planeBaseTime, planeTimeVariation;
	//Number of types of fixed planes.
	int numTypes;
	//Fixed planes parameters.
	FixedPlaneType *planeTypes;
	//Additional plane types:
	//Number of types of additional planes.
	int numExternalTypes;
	//External planes parameters.
	ExternalPlaneType *externalPlanesTypes;
}Parameters;

#endif
