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
	float m_Reflection;//the semi-reflexive mirror (~99%)
	float m_PrimaryPopInversionRadiation;
	float m_MeanFreePath;
	float m_MeanFreeTime;
	float m_EmissionsPerTravel;
	float m_EmissionsPerSecond;
	float m_OpticalDensity;//refractive index

public:
	ActiveMedium(unsigned int Z1, unsigned int Z2, float n = 1);
	//virtual ~ActiveMedium();
	void M_SetIncomingRadiation(float wavelength);
	void M_IdentifyNearestEmission();//closest after the pop. inversion from Z1
	void M_SetMeanFreePath(float density);//this sets the mean free path and time of the photons in the active medium
	void M_SetNoEmissionsPerLength(float photonsFromSource);
	void M_SetNoEmissionsPerTime();
	void M_setLength(float l);
};

