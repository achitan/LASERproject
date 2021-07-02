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
	ActiveMedium(unsigned int Z1, unsigned int Z2, float n = 1);//contructor for the AM, taking the emission atom Z1, the transparent atom Z2 and the optical density of the transparent medium
	virtual ~ActiveMedium() {};
	void M_SetIncomingRadiation(float wavelength);
	void M_IdentifyNearestEmission();//closest after (lower freq.) the pop. inversion of Z1
	void M_SetMeanFreePath(float density, float molecularDistance = 0);//this sets the mean free path and free time of the photons in the active medium, density should be in "per thousand"; the molecular distance parameter adds the crystaline netword constant, basically it adds some free space where nothing is - in pm
	void M_SetNoEmissionsPerLength();//considering MFP, this method computes the number of induced emissions for a single initial photon if it travels the entire length of the medium
	void M_SetNoEmissionsPerTime();//considering MFT, this method computes the number of induced emissions per second for a single photon travelling through the medium
	void M_SetLength(float l);//sets the length, in m, of the AM in the dimension parallel to the preferred direction of travel
};

