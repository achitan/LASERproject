#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::string operator"" _Z(unsigned long long z) {
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
		if (z == Z)
			break;
	}

	in.close();
	return Element;
}

std::string operator"" _nm(unsigned long long wl) {
	std::ifstream in("spectraVisibleEmissions.txt", std::ios::in);
	std::string line;
	float diff = 1000;
	float wavelength = 0;
	std::string element;
	while (!in.eof()) {
		std::getline(in, line);
		wavelength = atof(line.substr(line.find("\"") + 1, line.find("\"", line.find("\"") + 1) - line.find("\"")).c_str());
		if (fabs(wavelength - wl) < diff) {
			diff = fabs(wavelength - wl);
			element = line.substr(0, line.find("\t"));
		}
	}

	in.close();
	return element;
}

float operator"" _Zr(unsigned long long z) {
	std::ifstream in("periodic_table.txt", std::ios::in);
	std::vector<std::string> types = {"Gas","Metal","metal","Lanthanide","Actinide","Halogen"};
	std::string line;
	unsigned int Z;
	float radius = 0;
	while (!in.eof()) {
		std::getline(in, line);
		Z = atoi(line.substr(0, line.find(",")).c_str());
		if (z == Z)
			break;
	}
	in.close();
	auto iterTypes = types.begin();
	while (iterTypes != types.end()) {
		size_t comma = line.find(",", line.find(*iterTypes)) != std::string::npos ? line.find(",", line.find(*iterTypes)) + 1 : std::string::npos;
		if (comma != std::string::npos) {
			radius = atof(line.substr(comma, line.find(",", comma) - comma).c_str());
			break;
		}
		iterTypes++;
	}
	return radius;
}