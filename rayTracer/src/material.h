#pragma once

#include "ray.h"
#include "color.h"

struct hitRecord;

class material
{
public:
	virtual bool scatter(const ray& in, hitRecord& rec, color& attenuat, ray& scattered) const = 0;
};