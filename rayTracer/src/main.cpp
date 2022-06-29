#include <iostream>
#include <fstream>

#include "vec3.h"
#include "color.h"
#include "ray.h"
#include "constants.h"

#include "hittable.h"
#include "hittableList.h"
#include "sphere.h"

color rayColor(const ray& ray, const hittable& world)
{
	hitRecord rec;
	if (world.hit(ray, 0, infinity, rec))
	{
		return 0.5 * (rec.normal + color(1, 1, 1));
	}
	vec3 unitDirection = unitVector(ray.m_direction);
	double t = 0.5 * (unitDirection.y() + 1.0);
	return (color)((1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0));
}

int main()
{
	std::fstream file;
	file.open("src/image.ppm");

	if (!file)
		std::cout << "error: file not found" << std::endl;
	
	//image
	const double imgAspectRatio = 16.0 / 9.0;
	const int imgWidth = 640;
	const int imgHeight = (int)(imgWidth / imgAspectRatio);
	const int imgAlpha = 255;

	//world
	hittableList world;
	world.add(std::make_shared<sphere>(vec3(0, 0, -1), 0.5));
	world.add(std::make_shared<sphere>(vec3(0, -100.5, -1), 100));

	//camera
	const double viewportHeight = 2.0;
	const double viewportWidth = viewportHeight * imgAspectRatio;
	const double focalLength = 1.0;

	vec3 origin = vec3();
	vec3 horizontal = vec3(viewportWidth, 0, 0);
	vec3 vertical = vec3(0, viewportHeight, 0);
	vec3 upperLeftCorner = origin - horizontal / 2 + vertical / 2 - vec3(0, 0, focalLength);

	//render

	file << "P3" << std::endl << imgWidth << " " << imgHeight << std::endl << imgAlpha << std::endl;

	for (int i = 0; i < imgHeight; i++)
	{
		std::cout << "\rScanlines remaining: " << imgHeight - i << " " << std::flush;
		for (int j = 0; j < imgWidth; j++)
		{
			double u = double(j) / (imgWidth-1);
			double v = double(i) / (imgHeight-1);
			ray r(origin, upperLeftCorner + u * horizontal - v * vertical - origin);
			color color = rayColor(r, world);
			color.writeColor(file);
		}
	}

	std::cout << std::endl << "Done" << std::endl;

	file.close();
}