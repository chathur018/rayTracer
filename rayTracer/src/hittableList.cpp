#include "hittableList.h"

void hittableList::clear()
{
	m_objList.clear();
}

void hittableList::add(std::shared_ptr<hittable> object)
{
	m_objList.push_back(object);
}

bool hittableList::hit(const ray& ray, double tMin, double tMax, hitRecord& record) const
{
	bool hitAnyObj = false;
	hitRecord tempRec;
	double closestSoFar = tMax;

	for (const auto& object : m_objList)
	{
		if (object->hit(ray, tMin, closestSoFar, tempRec))
		{
			hitAnyObj = true;
			closestSoFar = tempRec.t;
			record = tempRec;
		}
	}

	return hitAnyObj;
}