#include "Camera.h"

// Shoots a fuckton of rays
void Camera::render() {

}

void Camera::createImage() {

}
/**
* Cast rays into the scene
* @param Scene the scene
* @return The maximum intensity found in the image
*/
double Camera::castRays(Scene& s) {
	double maximum = 0.0; // This will be overwritten when higher values are found
	std::cout << "Casting rays..." << std::endl;

	int count = 0, total = WIDTH * HEIGHT;
	for (auto& row : pixels) {
		for (Pixel& pixel : row) {
			// For our sanity, show progress:
			float progress = 100.0f * (float)count / total;

			std::cout << "\r" << progress << "%";

			// Cast rays for current pixel
			ColorDb color(0.0);
			std::vector<Ray> rays = pixel.getRayVector();
			for (Ray r : rays) {
				for (int i = 0; i < spp; i++) {
					color += castRay(s, r);
				}
			}

			color /= (double)(spp * subPixels * subPixels);
			pixel.setColor(color);
			maximum = glm::max(maximum, glm::max(color.r, glm::max(color.g, color.b)));	// Get the hightest value of the three channels
			count += 1;
		}
	}
	return maximum;
}

/**
* Cast a single ray
*/
ColorDb Camera::castRay(Scene& scene, Ray& ray, int depth) {
	// Get triangles from the scene that intersects the ray
	std::list<TriangleIntersection> intersections = scene.detectIntersections(ray);
	//TODO: Get spheres from the scene that intersects the ray

	// Will be overwritten
	ColorDb color(0.0);
	float distanceToTriangle = INFINITY;

	if (intersections.size() > 0) {
		distanceToTriangle = glm::distance(intersections.front().point, ray.GetStart());
	}
	if (!intersections.size()) {
		std::cout << "Miss (no intersection), ray origin: " << glm::to_string(ray.GetStart()) <<
			"ray direction: " << glm::to_string(ray.GetEnd()) << std::endl;
	}

	for (TriangleIntersection& intersection : intersections) {
		Triangle t = intersection.triangle;
		Surface surface = t.getSurface();

		// Area light test
		if (surface.HasReflectionModel(LIGHTSOURCE)) {
			color = surface.GetColor();
			break;
		}
		
		Direction normal = t.getNormal();
		Ray out = surface.bounceRay(ray, intersection.point, normal);
		double angle = glm::angle(out.GetEnd(), normal);
		ColorDb emittance = surface.reflect(ray, out, normal) * cos(angle);
		const ColorDb& lightContribution = scene.getLightContribution(intersection.point, normal);
		color += emittance;
		color *= lightContribution;

		// Check if we should exit loop
		double rrTop = glm::max(glm::max(emittance.r, emittance.g), emittance.b);
		if (depth < MAX_DEPTH || uniformRand() < rrTop) {
			int nextDepth = surface.HasReflectionModel(SPECULAR) ? depth : depth + 1;
			color += castRay(scene, out, nextDepth) * surface.GetReflectionCoefficient();
		}
		break;

	}

	return color;

}

/**
* Write image data to file according to filename
* @param filename name of file
* @param max maximum color value in image, used for normalization correction
*/
void Camera::writeToFile(std::string filename, const double& max) {
	std::cout << "Writing image... (Max: " << max << ")" << std::endl;
	FILE* fp = fopen(filename.c_str(), "wb");
	(void)fprintf(fp, "P3\n%d %d\n255\n", WIDTH, HEIGHT);
	for (auto& row : pixels) {
		for (Pixel& pixel : row) {
			ColorDb clr = pixel.getColor();
			(void)fprintf(fp, "%d %d %d",
				(int)(255 * (clr.r / max)),
				(int)(255 * (clr.g / max)),
				(int)(255 * (clr.b / max)));
		}
	}
	(void)fclose(fp);
	std::cout << "Wrote image to: '" << filename << "'." << std::endl;
}