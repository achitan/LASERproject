#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>

class ExternalSource {
private:
	std::map<float,float> m_OutputDecays;//output frequency, probability of decay
	float m_Area;
	float h = 6.62607004E-34;//m2 kg/s
	float c = 299792458;//m/s
	float pi = 3.1415926535;
	float m_OutputPower;//W

public:
	ExternalSource(float lambda);//monochromatic source
	ExternalSource(std::pair<float,float> lambda_prob);//polychromatic source w/ favourable color
	void M_IdentifyDecays();
	
	void M_SetPower(float power);
	void M_AddDecay(std::pair<float, float> lambda_prob);//add decay - it is checked for probability integration (=1)

	void M_RunFor(unsigned long time);//time in seconds to run the light
};

