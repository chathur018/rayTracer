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
	bool nearZero() const;

	vec3& operator+=(const vec3& v);
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

inline vec3 operator*(const vec3& u, const vec3& v)
{
	return vec3(u.x() * v.x(), u.y() * v.y(), u.z() * v.z());
}

inline vec3 operator/(const vec3& v, const double& t)
{
	return vec3(v.x() / t, v.y() / t, v.z() / t);
}

vec3 unitVector(const vec3& vec);

double dotProduct(const vec3& u, const vec3& v);

vec3 crossProduct(const vec3& u, const vec3& v);

vec3 reflect(const vec3& v, const vec3& n);

vec3 refract(vec3 v, vec3 n, const double refractiveIndex, const int& hitSide);

inline static vec3 random();

inline static vec3 random(double min, double max);

vec3 randomUnitVec();