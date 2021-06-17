#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <string>

class ExternalSource {
private:
	std::vector<unsigned int> m_Wavelengths;
	float m_Area;
	float h = 6.62607004E-34;//m2 kg/s
	float c = 299792458;//m/s
	float pi = 3.1415926535;
	float m_OutputPower;//W
	unsigned int m_Z;//atomic number
	std::string m_Symbol;

public:
	ExternalSource(unsigned int lambda);
	virtual ~ExternalSource() {};
	void M_IdentifyEmissions();
	void M_IdentifyElement();
	void M_SetPower(float power);

	void M_RunFor(unsigned long time);//time in seconds to run the light

};

