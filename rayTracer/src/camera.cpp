#include "camera.h"

camera::camera()
{
	const double imgAspectRatio = 16.0 / 9.0;
	const double viewportHeight = 2.0;
	const double viewportWidth = viewportHeight * imgAspectRatio;
	const double focalLength = 1.0;

	m_origin = vec3();
	m_horizontal = vec3(viewportWidth, 0, 0);
	m_vertical = vec3(0, viewportHeight, 0);
	m_upperLeftCorner = m_origin - m_horizontal / 2 + m_vertical / 2 - vec3(0, 0, focalLength);
}

ray camera::getRay(double u, double v) const
{
	return ray(m_origin, m_upperLeftCorner + u * m_horizontal - v * m_vertical - m_origin);
}