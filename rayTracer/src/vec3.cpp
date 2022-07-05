#include "vec3.h"

#include <cmath>

#include "constants.h"

vec3::vec3()
	: m_e{ 0, 0, 0 }
{
}

vec3::vec3(double e0, double e1, double e2)
	: m_e{ e0, e1, e2 }
{
}

vec3::~vec3()
{
}

double vec3::x() const
{
	return m_e[0];
}

double vec3::y() const
{
	return m_e[1];
}

double vec3::z() const
{
	return m_e[2];
}

double vec3::length() const
{
	return std::sqrt(m_e[0] * m_e[0] + m_e[1] * m_e[1] + m_e[2] * m_e[2]);
}

double vec3::lengthSquared() const
{
	return m_e[0] * m_e[0] + m_e[1] * m_e[1] + m_e[2] * m_e[2];
}

bool vec3::nearZero() const
{
	double z = 1e-8;

	return (fabs(m_e[0]) < z) && (fabs(m_e[1]) < z) && (fabs(m_e[2]) < z);
}

vec3 unitVector(const vec3& vec)
{
	return vec / vec.length();
}

double dotProduct(const vec3& u, const vec3& v)
{
	return u.m_e[0] * v.m_e[0] + u.m_e[1] * v.m_e[1] + u.m_e[2] * v.m_e[2];
}

vec3 crossProduct(const vec3& u, const vec3& v) {
	return vec3(u.m_e[1] * v.m_e[2] - u.m_e[2] * v.m_e[1],
		u.m_e[2] * v.m_e[0] - u.m_e[0] * v.m_e[2],
		u.m_e[0] * v.m_e[1] - u.m_e[1] * v.m_e[0]);
}

vec3 reflect(const vec3& v, const vec3& n)
{
	return v - 2 * dotProduct(v, n) * n;
}

//v and n need to be unit vectors
vec3 refract(vec3 v, vec3 n, double refractiveIndex, const int& hitSide)
{
	double normDot = dotProduct(v, n);
	vec3 perpendicularToNormal = (v - normDot * n) / refractiveIndex;
	vec3 parallelToNormal = - hitSide * std::sqrt(1.0 - perpendicularToNormal.lengthSquared()) * n;
	return perpendicularToNormal + parallelToNormal;
}

inline static vec3 random() {
	return vec3(randomDouble(), randomDouble(), randomDouble());
}

inline static vec3 random(double min, double max) {
	return vec3(randomDouble(min, max), randomDouble(min, max), randomDouble(min, max));
}

vec3 randomUnitVec()
{
	return unitVector(random());
}

vec3& vec3::operator+=(const vec3& v)
{
	m_e[0] += v.x();
	m_e[1] += v.y();
	m_e[2] += v.z();
	return *this;
}