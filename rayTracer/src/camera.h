#pragma once

#include "constants.h"
#include "vec3.h"
#include "ray.h"

class camera
{
public:
	vec3 m_origin;
	vec3 m_upperLeftCorner;
	vec3 m_horizontal;
	vec3 m_vertical;

	camera();

	ray getRay(double u, double v) const;
};