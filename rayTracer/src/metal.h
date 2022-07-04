#pragma once

#include "material.h"

class metal : public material
{
public:
	color m_albedo;
	double m_fuzz;

	metal(color a, double d)
		: m_albedo(a), m_fuzz(d < 1 ? d : 1)
	{}

	bool scatter(const ray& in, hitRecord& rec, color& attenuation, ray& scattered) const override
	{
		vec3 scatterDirection = reflect(in.m_direction, rec.normal) + m_fuzz * randomUnitVec();

		scattered = ray(rec.point, scatterDirection);
		attenuation = m_albedo;
		return (dotProduct(scatterDirection, rec.normal) > 0);
	}
};