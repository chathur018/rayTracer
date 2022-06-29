#pragma once

#include "ray.h"

struct hitRecord
{
	vec3 point;
	vec3 normal;
	double t;
};

class hittable
{
public:
	virtual bool hit(const ray& ray, double tMin, double tMax, hitRecord& record) const = 0;
};