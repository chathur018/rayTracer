#pragma once

#include "material.h"

#include "color.h"

class lambertian : public material
{
public:
	color m_albedo;

	lambertian(color a)
		: m_albedo(a)
	{}

	bool scatter(const ray& in, hitRecord& rec, color& attenuation, ray& scattered) const override
	{
		vec3 scatterDirection = randomUnitVec() + rec.hitSide * rec.normal;

		if (scatterDirection.nearZero())
			scatterDirection = rec.normal;

		scattered = ray(rec.point, scatterDirection);
		attenuation = m_albedo;
		return true;
	}
};