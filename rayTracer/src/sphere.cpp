#include "sphere.h"

#include <cmath>

sphere::sphere()
	: m_center(vec3()), m_radius(0)
{
}

sphere::sphere(const vec3& center, double radius)
	: m_center(center), m_radius(radius)
{
}

bool sphere::hit(const ray& ray, double tMin, double tMax, hitRecord& record) const
{
	vec3 temp = ray.m_origin - m_center;
	double a = dotProduct(ray.m_direction, ray.m_direction);
	double halfb = dotProduct(temp, ray.m_direction);
	double c = dotProduct(temp, temp) - m_radius * m_radius;
	
	double discriminant = halfb * halfb - a * c;
	if (discriminant < 0)
		return false;

	double sqrtd = std::sqrt(discriminant);
	double root = (-halfb - sqrtd) / a;
	if (root < tMin || tMax < root)
	{
		root = (-halfb + sqrtd) / a;
		if (root < tMin || tMax < root)
			return false;
	}

	record.t = root;
	record.point = ray.at(root);
	record.normal = (record.point - m_center) / m_radius;

	return true;
}