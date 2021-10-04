// LASERproject is a project to meet the needs for the "better eta laser"

#include <iostream>
#include <cmath>

#include "HelpingFunc.h"
#include "ExternalSource.h"
#include "ActiveMedium.h"

int main() {
	//ExternalSource source(980);
	//source.M_SetPower(1000);
	//source.M_RunFor(10);

	ActiveMedium am(70, 1.5, 33);
	am.M_SetIncomingRadiation(980);
	//am.M_IdentifyNearestEmission();
	am.M_SetMeanFreePath(1,1000);
	am.M_SetLength(1);
	am.M_ComputeEmissionsPerLength();
	am.M_ComputeEmissionsPerSec();
	
	//HELPING FUNCTIONS TEST
	//std::cout << 70_Z << std::endl;
	//std::cout << 1030_nm << std::endl;
	//std::cout << 70_Zr << std::endl;

	return EXIT_SUCCESS;
}