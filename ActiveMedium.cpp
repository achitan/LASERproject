#include "ActiveMedium.h"

ActiveMedium::ActiveMedium(unsigned int Z1, unsigned int Z2) {
	this->m_Reflection = 0.99;
	this->m_Zemission = Z1;
	this->m_Ztransparence = Z2;
	this->m_Reflection = 0.99;
}

void ActiveMedium::M_IdentifyMostProbableEmission() {
	//get all emissions from Z1
	std::vector<float> emissionsOfZ;
	std::ifstream in("periodic_table.txt", std::ios::in);
	unsigned int Z;
	std::string Element;
	std::string Symbol;
	std::string line;
	while (!in.eof()) {
		std::getline(in, line);
		Z = atoi(line.substr(0, line.find(",")).c_str());
		Element = line.substr(line.find(",") + 1, line.find(",", line.find(",") + 1) - line.find(",") - 1);
		Symbol = line.substr(line.find(",", line.find(",") + 1) + 1, line.find(",", line.find(",", line.find(",") + 1) + 1) - line.find(",", line.find(",") + 1) - 1);
		if (Z == this->m_Zemission)
			break;
	}
	in.close();

	in = std::ifstream("spectraVisibleEmissions.txt", std::ios::in);
	float wavelength = 0;
	while (!in.eof()) {
		std::getline(in, line);
		if (Symbol.compare(line.substr(0, line.find("\t"))) == 0) {
			wavelength = atof(line.substr(line.find("\"") + 1, line.find("\"", line.find("\"") + 1) - line.find("\"")).c_str());
			if (wavelength > 200)
				emissionsOfZ.push_back(wavelength);
		}
	}
	std::sort(std::execution::par_unseq, emissionsOfZ.begin(), emissionsOfZ.end());

	for (auto wl : emissionsOfZ) {
		if (wl > this->m_PrimaryPopInversionRadiation) {
			this->m_Emission = wl;
			break;
		}
	}

	std::cout << "=====================ACTIVE MEDIUM=====================" << std::endl;
	std::cout << "THE ACTIVE MEDIUM EMITS AT " << this->m_Emission << " nm" << std::endl;
	std::cout << "=====================================================" << std::endl;
}

void ActiveMedium::M_SetIncomingRadiation(float wavelength) {
	this->m_PrimaryPopInversionRadiation = wavelength;
}