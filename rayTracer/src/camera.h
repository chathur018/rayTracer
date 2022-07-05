#pragma once


#include "vec3.h"
#include "ray.h"

class camera
{
public:
	vec3 m_origin;
	vec3 m_upperLeftCorner;
	vec3 m_horizontal;
	vec3 m_vertical;
	vec3 u, v, w;
	double m_lensRadius;

	camera(vec3 lookfrom, vec3 lookat, vec3 vup, double vfov, double aspectRatio, double aperture, double focusDist);

	ray getRay(double u, double v) const;
};