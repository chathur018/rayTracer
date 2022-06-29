#pragma once

#include "hittable.h"

#include <vector>
#include <memory>

class hittableList : public hittable
{
public:
	std::vector<std::shared_ptr<hittable>> m_objList;

	hittableList(){}

	void clear();
	void add(std::shared_ptr<hittable> object);

	bool hit(const ray& ray, double tMin, double tMax, hitRecord& record) const override;
};