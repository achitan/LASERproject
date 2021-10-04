#include "ActiveMedium.h"

ActiveMedium::ActiveMedium(unsigned int Z1, float n, unsigned int Z2) {
	this->m_Reflection = 0.99;
	this->m_Zemission = Z1;
	this->m_Ztransparence = Z2;
	this->m_OpticalDensity = n;
}

void ActiveMedium::M_IdentifyNearestEmission() {
	//get all emissions of Z1
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
			if (wavelength > 199)
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

void ActiveMedium::M_SetMeanFreePath(float density, float molecularDistance) {
	std::ifstream in("periodic_table.txt", std::ios::in);
	std::vector<std::string> types = { "Gas","Metal","metal","Lanthanide","Actinide","Halogen" };
	std::string lineEmission;
	std::string lineTransparence;
	std::string line;
	unsigned int Z;
	float radiusEmission = 0;//the radius of the emitting atom
	float radiusTransparence = 0;//the radius of the refractive medium
	while (!in.eof()) {
		std::getline(in, line);
		Z = atoi(line.substr(0, line.find(",")).c_str());
		if (this->m_Zemission == Z)
			lineEmission = line;
		else if (this->m_Ztransparence == Z)
			lineTransparence = line;
		else if (lineTransparence.size() && lineEmission.size())
			break;
	}
	in.close();
	auto iterTypes = types.begin();
	while (iterTypes != types.end()) {
		size_t commaEmission = lineEmission.find(",", lineEmission.find(*iterTypes)) != std::string::npos ? lineEmission.find(",", lineEmission.find(*iterTypes)) + 1 : std::string::npos;
		size_t commaTransparence = lineTransparence.find(",", lineTransparence.find(*iterTypes)) != std::string::npos ? lineTransparence.find(",", lineTransparence.find(*iterTypes)) + 1 : std::string::npos;
		if (commaEmission != std::string::npos)
			radiusEmission = atof(lineEmission.substr(commaEmission, lineEmission.find(",", commaEmission) - commaEmission).c_str());
		if (commaTransparence != std::string::npos)
			radiusTransparence = atof(lineTransparence.substr(commaTransparence, lineTransparence.find(",", commaTransparence) - commaTransparence).c_str()) + molecularDistance;
		if (radiusEmission && radiusTransparence)
			break;
		iterTypes++;
	}

	//TOTAL DISTANCE OF A STRING OF ATOMS IN THE ACTIVE MEDIUM
	float transparenceAtomNo = 1000. / density - 1;
	//float emissionAtomNo = density;
	float path = transparenceAtomNo * (radiusTransparence + molecularDistance) * 1E-12;//a photon travels freely through the transparent medium atoms and the space between the nodes of the crystaline net.
	this->m_MeanFreePath = path;//[m]
	this->m_MeanFreeTime = path / 299792458. / this->m_OpticalDensity;
}

void ActiveMedium::M_ComputeEmissionsPerLength() {
	this->m_EmissionsPerTravel = this->m_Length / this->m_MeanFreePath;
}

void ActiveMedium::M_ComputeEmissionsPerSec() {
	this->m_EmissionsPerSecond = 1 / this->m_MeanFreeTime;
}

void ActiveMedium::M_SetLength(float l) {
	this->m_Length = l;
}