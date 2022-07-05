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

#include "material.h"
#include "lambertian.h"
#include "metal.h"
#include "dielectric.h"

void randomSceneGenerator(hittableList& world)
{
	std::shared_ptr<lambertian> ground_material = std::make_shared<lambertian>(color(0.5, 0.5, 0.5));
	world.add(std::make_shared<sphere>(vec3(0, -1000, 0), 1000, ground_material));

	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			double choose_mat = randomDouble();
			vec3 center(a + 0.9 * randomDouble(), 0.2, b + 0.9 * randomDouble());

			if ((center - vec3(4, 0.2, 0)).length() > 0.9) {
				std::shared_ptr<material> sphere_material;

				if (choose_mat < 0.8) {
					// diffuse
					color albedo = randomColor() * randomColor();
					sphere_material = std::make_shared<lambertian>(albedo);
					world.add(std::make_shared<sphere>(center, 0.2, sphere_material));
				}
				else if (choose_mat < 0.95) {
					// metal
					color albedo = randomColor(0.5, 1);
					double fuzz = randomDouble(0, 0.5);
					sphere_material = std::make_shared<metal>(albedo, fuzz);
					world.add(std::make_shared<sphere>(center, 0.2, sphere_material));
				}
				else {
					// glass
					sphere_material = std::make_shared<dielectric>(1.5);
					world.add(std::make_shared<sphere>(center, 0.2, sphere_material));
				}
			}
		}
	}

	std::shared_ptr<dielectric> material1 = std::make_shared<dielectric>(1.5);
	world.add(std::make_shared<sphere>(vec3(0, 1, 0), 1.0, material1));

	std::shared_ptr<lambertian> material2 = std::make_shared<lambertian>(color(0.4, 0.2, 0.1));
	world.add(std::make_shared<sphere>(vec3(-4, 1, 0), 1.0, material2));

	std::shared_ptr<metal> material3 = std::make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
	world.add(std::make_shared<sphere>(vec3(4, 1, 0), 1.0, material3));

}

color rayColor(const ray& r, const hittable& world, int depth)
{
	if (depth <= 0)
		return color(0, 0, 0);
	
	hitRecord rec;
	if (world.hit(r, 0.001, infinity, rec))
	{
		ray scattered;
		color attenuation;
		if (rec.matPtr->scatter(r, rec, attenuation, scattered))
			return attenuation * rayColor(scattered, world, depth - 1);
		return color(0, 0, 0);
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
	const double imgAspectRatio = 3.0 / 2.0;
	const int imgWidth = 1200;
	const int imgHeight = (int)(imgWidth / imgAspectRatio);
	const int imgAlpha = 255;
	const int samplesPerPixel = 500;
	const int maxDepth = 50;

	//world
	hittableList world;

	randomSceneGenerator(world);

	/*
	std::shared_ptr<lambertian> material_ground = std::make_shared<lambertian>(color(0.8, 0.8, 0.0));
	std::shared_ptr<lambertian> material_center = std::make_shared<lambertian>(color(0.1, 0.2, 0.5));
	std::shared_ptr<dielectric> material_left = std::make_shared<dielectric>(1.5);
	std::shared_ptr<metal> material_right = std::make_shared<metal>(color(0.8, 0.6, 0.2), 0.0);

	world.add(std::make_shared<sphere>(vec3(0.0, -100.5, -1.0), 100.0, material_ground));
	world.add(std::make_shared<sphere>(vec3(0.0, 0.0, -1.0), 0.5, material_center));
	world.add(std::make_shared<sphere>(vec3(-1.0, 0.0, -1.0), 0.5, material_left));
	world.add(std::make_shared<sphere>(vec3(-1.0, 0.0, -1.0), -0.45, material_left));
	world.add(std::make_shared<sphere>(vec3(1.0, 0.0, -1.0), 0.5, material_right));
	*/

	//camera
	vec3 lookfrom(13, 2, 3);
	vec3 lookat(0, 0, 0);
	vec3 vup(0, 1, 0);
	double distToFocus = 10.0;
	double aperture = 0.1;
	camera camera(lookfrom, lookat, vup, 20, imgAspectRatio, aperture, distToFocus);

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