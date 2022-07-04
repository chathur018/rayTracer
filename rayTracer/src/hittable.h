#pragma once

#include "ray.h"
#include "material.h"

#include <memory>

struct hitRecord
{
	vec3 point;
	vec3 normal;
	std::shared_ptr<material> matPtr;
	double t = 0;
	int hitSide = 0;
};

class hittable
{
public:
	virtual bool hit(const ray& ray, double tMin, double tMax, hitRecord& record) const = 0;
};