// LASERproject is a project to meet the needs for the "better eta laser"

#include <iostream>
#include <cmath>

#include "HelpingFunc.h"
#include "ExternalSource.h"
#include "ActiveMedium.h"

int main() {
	ExternalSource Na(980);
	//Na.M_AddDecay(std::make_pair(980, 0.4));
	Na.M_SetPower(1000);
	Na.M_RunFor(10);
	//Na.M_IdentifyDecays();

	ActiveMedium Yb(1, 2);
	//std::cout << 70_Z << std::endl;
	std::cout << 1030_nm << std::endl;

	return EXIT_SUCCESS;
}