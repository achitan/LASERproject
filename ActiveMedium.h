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
	virtual ~ActiveMedium() {};
	void M_SetIncomingRadiation(float wavelength);
	void M_IdentifyNearestEmission();//closest after the pop. inversion of Z1
	void M_SetMeanFreePath(float density, float molecularDistance = 0);//this sets the mean free path and free time of the photons in the active medium; the molecular distance parameter adds the crystaline netword constant - in pm
	void M_SetNoEmissionsPerLength(float photonsFromSource);
	void M_SetNoEmissionsPerTime();
	void M_SetLength(float l);
};

