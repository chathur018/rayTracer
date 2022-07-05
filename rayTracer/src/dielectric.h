#pragma once

#include "material.h"

//#include <cmath>

class dielectric : public material
{
public:
	double m_refractiveIndex;

	dielectric(const double r)
		: m_refractiveIndex(r)
	{}

	bool scatter(const ray& in, hitRecord& rec, color& attenuation, ray& scattered) const override
	{
		double relativeIndex = m_refractiveIndex;
		if (rec.hitSide < 0)
			relativeIndex = 1 / relativeIndex;

		vec3 outDirection;

		vec3 unitInDirection = unitVector(in.m_direction);
		vec3 unitNormal = unitVector(rec.normal);
		double cos = dotProduct(unitInDirection, unitNormal);

		if ((std::sqrt(1.0 - cos * cos)) / relativeIndex > 1.0 
			|| reflectance(fabs(cos), relativeIndex) > randomDouble())
			outDirection = reflect(unitInDirection, unitNormal);
		else		
			outDirection = refract(unitInDirection, unitNormal, relativeIndex, rec.hitSide);

		scattered = ray(rec.point, outDirection);

		attenuation = color(1.0, 1.0, 1.0);
		return true;
	}

private:
	static double reflectance(double cosine, double refIdx) {
		// Use Schlick's approximation for reflectance.
		double r0 = (1 - refIdx) / (1 + refIdx);
		r0 = r0 * r0;
		return r0 + (1 - r0) * pow((1 - cosine), 5);
	}
};