#pragma once

#include <iostream>
#include <cmath>

void IdentifyBestDecay(float wavelength) {
	float h = 6.62607004E-34;//m2 kg/s
	float c = 299792458;//m/s
	float energ = h * c / (wavelength * 1E-9);
	float diff = 1000;
	unsigned int n_f = 0;
	unsigned int n_i = 0;
	unsigned int Z_atom = 0;
	float energQuanta = 0;
	for (unsigned int Z = 1; Z <= 118; Z++) {
		for (unsigned int n_initial = 2; n_initial < 8; n_initial++) {
			for (unsigned int n_final = n_initial - 1; n_final > 0; n_final--) {
				energQuanta = -13.6 * pow(Z, 2) * 1.60218E-19;
				energQuanta *= (1 / pow(n_final, 2) - 1 / pow(n_initial, 2));
				if (diff > abs(energ + energQuanta)) {
					diff = abs(energ + energQuanta);
					Z_atom = Z;
					n_i = n_initial;
					n_f = n_final;
				}
			}
		}
	}
	std::cout << "==================IDENTIFY BEST DECAY==================" << std::endl;
	std::cout << "ATOMIC EMISSION AT " << wavelength << " nm" << std::endl;
	std::cout << "Z: " << Z_atom << std::endl;
	std::cout << "TRANZITION FROM " << n_i << " TO " << n_f << std::endl;
	std::cout << "=======================================================" << std::endl;
}

void IdentifyBestDecayInAtom(float wavelength, unsigned int Z) {
	float h = 6.62607004E-34;//m2 kg/s
	float c = 299792458;//m/s
	float energ = h * c / (wavelength * 1E-9);
	float diff = 1000;
	unsigned int n_f = 0;
	unsigned int n_i = 0;
	unsigned int Z_atom = Z;
	float energQuanta = 0;
	float actualWavelength = 0;
	for (unsigned int n_initial = 2; n_initial < 8; n_initial++) {
		for (unsigned int n_final = n_initial - 1; n_final > 0; n_final--) {
			energQuanta = -13.6 * pow(Z, 2) * 1.60218E-19;
			energQuanta *= (1 / pow(n_final, 2) - 1 / pow(n_initial, 2));
			if (diff > abs(energ + energQuanta)) {
				diff = abs(energ + energQuanta);
				n_i = n_initial;
				n_f = n_final;
				actualWavelength = h * c / energQuanta * (-1E9);
			}
		}
	}
	std::cout << "=============IDENTIFY BEST DECAY IN ATOM===============" << std::endl;
	std::cout << "ATOMIC EMISSION AT " << wavelength << " nm" << std::endl;
	std::cout << "Z: " << Z_atom << std::endl;
	std::cout << "TRANZITION FROM " << n_i << " TO " << n_f << std::endl;
	std::cout << "ACTUAL WAVELENGTH: " << actualWavelength << " nm" << std::endl;
	std::cout << "=======================================================" << std::endl;
}

void DegeneracyLevels() {

}