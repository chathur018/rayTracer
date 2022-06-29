#pragma once

#include "vec3.h"

#include <iostream>

class color : public vec3
{
public:
	color(){}
	color(double e0, double e1, double e2)
	{
		m_e[0] = e0;
		m_e[1] = e1;
		m_e[2] = e2;
	}
	color(const vec3& v)
	{
		m_e[0] = v.x();
		m_e[1] = v.y();
		m_e[2] = v.z();
	}
	
	void writeColor(std::ostream& out)
	{
		out << (int)(255.999 * this->x()) << " "
			<< (int)(255.999 * this->y()) << " "
			<< (int)(255.999 * this->z()) << std::endl;
	}
};