#include "ExternalSource.h"

ExternalSource::ExternalSource(unsigned int lambda) {
	if (lambda > 118) {
		this->m_Wavelengths.push_back(lambda);
		this->M_IdentifyElement();
	}
	else {
		this->m_Z = lambda;
		this->M_IdentifyEmissions();
	}

	std::cout << "DON'T FORGET TO ALSO SET THE OUTPUT POWER OF THE SOURCE" << std::endl;
}

void ExternalSource::M_SetPower(float power) {
	this->m_OutputPower = power;
	//std::cout << "POWER SET" << std::endl;
	/*auto iterDecays = this->m_OutputDecays.begin();

	std::cout << "===================PUMP ESTABLISHED====================" << std::endl;
	std::cout << "THIS PUMP EMITS IN: " << iterDecays->first << " nm (" << c / iterDecays->first / 1E-9 << " Hz)";
	++iterDecays;
	while (iterDecays != this->m_OutputDecays.end()) {
		std::cout << ", " << iterDecays->first << " nm (" << c / iterDecays->first / 1E-9 << " Hz)";
		++iterDecays;
	}
	std::cout << "." << std::endl;
	std::cout << "POWER OUTPUT: " << power << " W" << std::endl;
	std::cout << "=======================================================" << std::endl;*/
}

void ExternalSource::M_RunFor(unsigned long time) {//time in nanoseconds
	//std::srand(std::time(NULL));
	/*auto iterDecays = this->m_OutputDecays.begin();
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
	std::cout << "=======================================================" << std::endl;*/
}

void ExternalSource::M_IdentifyEmissions() {
	std::ifstream in("periodic_table.txt", std::ios::in);
	std::string line;
	unsigned int Z;
	std::string Element;
	std::string Symbol;
	while (!in.eof()) {
		std::getline(in, line);
		Z = atoi(line.substr(0, line.find(",")).c_str());
		Element = line.substr(line.find(",") + 1, line.find(",", line.find(",") + 1) - line.find(",") - 1);
		Symbol = line.substr(line.find(",", line.find(",") + 1) + 1, line.find(",", line.find(",", line.find(",") + 1) + 1) - line.find(",", line.find(",") + 1) - 1);
		if (this->m_Z == Z)
			break;
	}
	in.close();

	std::string element = Symbol;
	in = std::ifstream("spectraVisibleEmissions.txt", std::ios::in);
	//std::string line;
	float wavelength = 0;
	while (!in.eof()) {
		std::getline(in, line);
		if (element.compare(line.substr(0, line.find("\t"))) == 0) {
			wavelength = atof(line.substr(line.find("\"") + 1, line.find("\"", line.find("\"") + 1) - line.find("\"")).c_str());
			this->m_Wavelengths.push_back(wavelength);
		}
	}
	std::cout << "========================SOURCE=======================" << std::endl;
	std::cout << "YOU HAVE SET A SOURCE OF " << this->m_Z << std::endl;
	std::cout << "=====================================================" << std::endl;
}

void ExternalSource::M_IdentifyElement() {
	std::ifstream in("spectraVisibleEmissions.txt", std::ios::in);
	std::string line;
	float diff = 1000;
	float wavelength = 0;
	std::string element;
	while (!in.eof()) {
		std::getline(in, line);
		wavelength = atof(line.substr(line.find("\"") + 1, line.find("\"", line.find("\"") + 1) - line.find("\"")).c_str());
		if (fabs(wavelength - this->m_Wavelengths.at(0)) < diff) {
			diff = fabs(wavelength - this->m_Wavelengths.at(0));
			element = line.substr(0, line.find("\t"));
		}
	}
	std::cout << "========================SOURCE=======================" << std::endl;
	std::cout << "YOU HAVE SET A SOURCE EMITTING AT: " << this->m_Wavelengths.at(0) << " nm" << std::endl;
	std::cout << "CLOSEST ELEMENT EMITTING THIS WAVE IS: " << element << std::endl;
	std::cout << "=====================================================" << std::endl;
}