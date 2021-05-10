#include "ActiveMedium.h"

ActiveMedium::ActiveMedium(unsigned int Z1, unsigned int Z2) {
	this->m_Reflection = 0.99;
	this->m_Zemission = Z1;
	this->m_Ztransparence = Z2;
}