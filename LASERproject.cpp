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
	//IdentifyBestDecay(700);
	IdentifyBestDecayInAtom(1030, 70);

	return EXIT_SUCCESS;
}