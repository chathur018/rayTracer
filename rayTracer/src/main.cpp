#include <iostream>
#include <fstream>

#include "vec3.h"
#include "color.h"
#include "ray.h"
#include "constants.h"
#include "camera.h"

#include "hittable.h"
#include "hittableList.h"
#include "sphere.h"

color rayColor(const ray& r, const hittable& world, int depth)
{
	if (depth <= 0)
		return color(0, 0, 0);
	
	hitRecord rec;
	if (world.hit(r, 0.001, infinity, rec))
	{
		vec3 nextDirection = randomUnitVec() + rec.hitSide * rec.normal;
		return 0.5 * rayColor(ray(rec.point, nextDirection), world, depth - 1);
	}

	//background
	vec3 unitDirection = unitVector(r.m_direction);
	double t = 0.5 * (unitDirection.y() + 1.0);
	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main()
{
	std::fstream file;
	file.open("image.ppm");

	if (!file)
		std::cout << "error: file not found" << std::endl;
	
	//image
	const double imgAspectRatio = 16.0 / 9.0;
	const int imgWidth = 400;
	const int imgHeight = (int)(imgWidth / imgAspectRatio);
	const int imgAlpha = 255;
	const int samplesPerPixel = 100;
	const int maxDepth = 50;

	//world
	hittableList world;
	world.add(std::make_shared<sphere>(vec3(0, 0, -1), 0.5));
	world.add(std::make_shared<sphere>(vec3(0, -100.5, -1), 100));

	//camera
	camera camera;

	//render

	file << "P3" << std::endl << imgWidth << " " << imgHeight << std::endl << imgAlpha << std::endl;

	for (int i = 0; i < imgHeight; i++)
	{
		std::cout << "\rScanlines remaining: " << imgHeight - i - 1 << " " << std::flush;
		for (int j = 0; j < imgWidth; j++)
		{
			color pixelColor(0, 0, 0);

			for (int s = 0; s < samplesPerPixel; s++)
			{
				double u = (j + randomDouble()) / (imgWidth - 1);
				double v = (i + randomDouble()) / (imgHeight - 1);
				ray r = camera.getRay(u, v);
				pixelColor += rayColor(r, world, maxDepth);
			}

			//sample scaling and gamma correction
			double scale = 1.0 / samplesPerPixel;
			pixelColor.m_e[0] = sqrt(pixelColor.x() * scale);
			pixelColor.m_e[1] = sqrt(pixelColor.y() * scale);
			pixelColor.m_e[2] = sqrt(pixelColor.z() * scale);

			pixelColor.writeColor(file);
		}
	}

	std::cout << std::endl << "Done" << std::endl;

	file.close();
}