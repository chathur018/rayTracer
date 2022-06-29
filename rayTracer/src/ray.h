#pragma once

#include "vec3.h"

class ray
{
public:
	vec3 m_origin;
	vec3 m_direction;

	ray(){}
	ray(const vec3& origin, const vec3& direction);

	vec3 at(double t) const;
};