#pragma once

#include "hittable.h"

class sphere : public hittable
{
public:
	vec3 m_center;
	double m_radius;
	std::shared_ptr<material> m_matPtr;

	sphere();
	sphere(const vec3& center, double radius, std::shared_ptr<material> mat);

	bool hit(const ray& ray, double tMin, double tMax, hitRecord& record) const override;
};