#pragma once

#include "vec3.h"

#include "constants.h"

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
		out << (int)(256 * clamp(this->x(), 0.0, 0.999)) << " "
			<< (int)(256 * clamp(this->y(), 0.0, 0.999)) << " "
			<< (int)(256 * clamp(this->z(), 0.0, 0.999)) << std::endl;
	}
};

inline color operator+(const color& u, const color& v)
{
	return vec3(u.x() + v.x(), u.y() + v.y(), u.z() + v.z());
}

inline static color randomColor() {
	return color(randomDouble(), randomDouble(), randomDouble());
}

inline static color randomColor(double min, double max) {
	return color(randomDouble(min, max), randomDouble(min, max), randomDouble(min, max));
}