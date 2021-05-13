#include "ExternalSource.h"

ExternalSource::ExternalSource(float lambda) {
	this->m_OutputDecays[lambda] = 1;

	std::cout << "DON'T FORGET TO ALSO SET THE OUTPUT POWER OF THE SOURCE" << std::endl;
}

ExternalSource::ExternalSource(std::pair<float, float> lambda_prob) {
	this->m_OutputDecays[lambda_prob.first] = lambda_prob.second;

	std::cout << "DON'T FORGET TO ALSO SET THE OUTPUT POWER OF THE SOURCE" << std::endl;
}

//ExternalSource::ExternalSource(unsigned int Z) {

//}

void ExternalSource::M_AddDecay(std::pair<float, float> lambda_prob) {
	this->m_OutputDecays[lambda_prob.first] = lambda_prob.second;

	auto iterTranzitions = this->m_OutputDecays.begin();
	float sumProb = 0;
	while (iterTranzitions != this->m_OutputDecays.end()) {
		sumProb += iterTranzitions->second;
		++iterTranzitions;
	}
	if (sumProb > 1) {
		std::cout << "Probability sum cannot go ever 100%. Revize decays!" << std::endl;
		std::exit(1);
	}
}

void ExternalSource::M_SetPower(float power) {
	this->m_OutputPower = power;
	//std::cout << "POWER SET" << std::endl;
	auto iterDecays = this->m_OutputDecays.begin();

	std::cout << "===================PUMP ESTABLISHED====================" << std::endl;
	std::cout << "THIS PUMP EMITS IN: " << iterDecays->first << " nm (" << c / iterDecays->first / 1E-9 << " Hz)";
	++iterDecays;
	while (iterDecays != this->m_OutputDecays.end()) {
		std::cout << ", " << iterDecays->first << " nm (" << c / iterDecays->first / 1E-9 << " Hz)";
		++iterDecays;
	}
	std::cout << "." << std::endl;
	std::cout << "POWER OUTPUT: " << power << " W" << std::endl;
	std::cout << "=======================================================" << std::endl;
}

void ExternalSource::M_RunFor(unsigned long time) {//time in nanoseconds
	//std::srand(std::time(NULL));
	auto iterDecays = this->m_OutputDecays.begin();
	float totalEnergy = this->m_OutputPower * time * 1E-9;
	float sumEnergy = 0;
	while (iterDecays != this->m_OutputDecays.end()) {
		sumEnergy += h * c / (iterDecays->first * 1E-9) * iterDecays->second;
		++iterDecays;
	}
	std::cout << "=====================RUNNING PUMP======================" << std::endl;
	std::cout << "AFTER RUNNING FOR " << time << " ns," << std::endl;
	std::cout << "IT GENERATED " << totalEnergy / sumEnergy << " photons." << std::endl;
	std::cout << "FLUX [photons/sr]: " << totalEnergy / sumEnergy / 4 / pi << std::endl;
	std::cout << "=======================================================" << std::endl;
}

void ExternalSource::M_IdentifyDecays() {
	auto iterDecays = this->m_OutputDecays.begin();
	float energ = 0;
	float diff = 1000;
	unsigned int n_f = 0;
	unsigned int n_i = 0;
	unsigned int Z_atom = 0;
	float energQuanta = 0;
	while (iterDecays != this->m_OutputDecays.end()) {
		energ = h * c / (iterDecays->first * 1E-9);
		for (unsigned int Z = 1; Z <= 118; Z++) {
			for (unsigned int n_initial = 1; n_initial < 7; n_initial++) {
				//for (unsigned int n_final = n_initial+1; n_final < 8; n_final++) {
				unsigned int n_final = n_initial + 1;
				energQuanta = -13.6 * pow(Z, 2) * 1.60218E-19;
				energQuanta *= (1 / pow(n_final, 2) - 1 / pow(n_initial, 2));
				if (diff > abs(energ - energQuanta)) {
					diff = abs(energ - energQuanta);
					Z_atom = Z;
					n_i = n_initial;
					n_f = n_final;
				}
				//}
			}
		}
		++iterDecays;
	}
	std::cout << "ATOMIC PROPERTIES: " << std::endl;
	std::cout << "Z: " << Z_atom << std::endl;
	std::cout << "TRANZITION FROM " << n_i << " TO " << n_f << std::endl;
}