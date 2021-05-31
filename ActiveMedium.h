#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <execution>

class ActiveMedium {
private:
	unsigned int m_Zemission;
	unsigned int m_Ztransparence;
	float m_Emission;
	float m_Length;
	float m_Reflection;//the semi-reflexive mirror (~1%)
	float m_PrimaryPopInversionRadiation;

public:
	ActiveMedium(unsigned int Z1, unsigned int Z2);
	//virtual ~ActiveMedium();
	void M_SetIncomingRadiation(float wavelength);
	void M_IdentifyNearestEmission();//most probable after the pop inversion from Z1
};

