#ifndef __PARAMETERS_H__
#define __PARAMETERS_H__

/*************************************
 * A plane whose frequency is fixed. *
 *************************************/
typedef struct sFixedPlaneTypeParameters{
	float arrivalBaseTime, arrivalTimeVariation;
	float baseLoadingTime, loadingVariationTime;
	float cat3LandingGearProbability;
}FixedPlaneTypeParameters;

/*************************************
 * A set of planes of specific size. *
 *************************************/
typedef struct sExternalPlaneType{
	int numPlanes;
	float baseLoadingTime, loadingVariationTime;
	float baseRTTime, RTVariationTime;
	float cat3LandingGearProbability;
}ExternalPlaneType;

/*******************
 * The parameters. *
 *******************/
typedef struct sParameters{
	//Duration of the simulation.
	float simLength;
	//Storm timing parameters.
	float stormMean, stormBaseTime, stormTimeVariation;
	//Airport parameters:
	//Number of berths and taxiways.
	int numBerths, numTaxiways;
	//Time it takes to berth, deberth and travel across the taxiway.
	float taxiwayTravelTime, berthingTime;
	//Fixed plane parameters.
	FixedPlaneTypeParameters fixedPlaneTypeParameters;
	//Additional plane types:
	//Number of types of additional planes.
	int numExternalPlaneTypes;
	//External planes parameters.
	ExternalPlaneType *externalPlaneTypes;
}Parameters;

#endif
