#pragma once

class vec3
{
public:
	double m_e[3];

	vec3();
	vec3(double e0, double e1, double e2);
	~vec3();

	double x() const;
	double y() const;
	double z() const;

	double length() const;
	double lengthSquared() const;
};

inline vec3 operator+(const vec3& u, const vec3& v)
{
	return vec3(u.x() + v.x(), u.y() + v.y(), u.z() + v.z());
}

inline vec3 operator-(const vec3& u, const vec3& v)
{
	return vec3(u.x() - v.x(), u.y() - v.y(), u.z() - v.z());
}

inline vec3 operator*(const double& t, const vec3& v)
{
	return vec3(t * v.x(), t * v.y(), t * v.z());
}

inline vec3 operator/(const vec3& v, const double& t)
{
	return vec3(v.x() / t, v.y() / t, v.z() / t);
}

vec3 unitVector(const vec3& vec);

double dotProduct(const vec3& u, const vec3& v);