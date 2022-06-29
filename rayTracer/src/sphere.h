#pragma once

#include "hittable.h"

class sphere : public hittable
{
public:
	vec3 m_center;
	double m_radius;

	sphere();
	sphere(const vec3& center, double radius);

	bool hit(const ray& ray, double tMin, double tMax, hitRecord& record) const override;
};