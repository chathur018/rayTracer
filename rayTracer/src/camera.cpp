#include "camera.h"

#include "constants.h"

camera::camera(vec3 lookfrom, vec3 lookat, vec3 vup, double vfov, 
	double aspectRatio, double aperture, double focusDist)
{
	double theta = degreesToRadians(vfov);
	const double viewportHeight = 2.0 * tan(theta/2);
	const double viewportWidth = viewportHeight * aspectRatio;
	const double focalLength = 1.0;

	w = unitVector(lookfrom - lookat);
	u = unitVector(crossProduct(vup, w));
	v = crossProduct(w, u);

	m_origin = lookfrom;
	m_horizontal = focusDist * viewportWidth * u;
	m_vertical = focusDist * viewportHeight * v;
	m_upperLeftCorner = m_origin - m_horizontal / 2 + m_vertical / 2 - focusDist * w;

	m_lensRadius = aperture / 2;
}

ray camera::getRay(double s, double t) const
{
	vec3 rd = m_lensRadius * randomUnitVec();
	vec3 offset = rd.x() * u + rd.y() * v;
	
	return ray(m_origin + offset, m_upperLeftCorner + s * m_horizontal - t * m_vertical - m_origin - offset);
}