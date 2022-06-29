#include "ray.h"

ray::ray(const vec3& origin, const vec3& direction)
	: m_origin(origin), m_direction(direction)
{
}

vec3 ray::at(double t) const
{
	return m_origin + t * m_direction;
}