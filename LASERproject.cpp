// LASERproject is a project to meet the needs for the "better eta laser"

#include <iostream>
#include <cmath>

#include "HelpingFunc.h"
#include "ExternalSource.h"
#include "ActiveMedium.h"

int main() {
	ExternalSource source(70);
	source.M_SetPower(1000);
	source.M_RunFor(10);
	
	//std::cout << 70_Z << std::endl;
	//std::cout << 1030_nm << std::endl;

	return EXIT_SUCCESS;
}