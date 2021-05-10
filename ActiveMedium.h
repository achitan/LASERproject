#pragma once

#include <iostream>


class ActiveMedium {
private:
	unsigned int m_Zemission;
	unsigned int m_Ztransparence;
	float m_Length;
	float m_Reflection;//the semi-reflexive mirror (~99%)

public:
	ActiveMedium(unsigned int Z1, unsigned int Z2);
};

