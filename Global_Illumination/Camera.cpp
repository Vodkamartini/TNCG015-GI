#include "Camera.h"
#include <fstream>
#include <chrono>

void Camera::switchEye() {
	if (_using_eye1)
		_using_eye1 = false;
	else
		_using_eye1 = true;
}

void Camera::render(Scene* scene) {
	printf("\nRendering scene...\n");
	size_t count = 0, total = _pixels.size();

	ColorDbl finalColor(0.0, 0.0, 0.0);
	Pixel thisPixel;

	float pixelSizeY = 2 / (float)_pixels.width();
	float pixelSizeZ = 2 / (float)_pixels.height();

	float halfPixelY = pixelSizeY / 2.0f;
	float halfPixelZ = pixelSizeZ / 2.0f;
	Vertex activeEye = _using_eye1 ? _eye1 : _eye2;

	float x = 0.0f, y = -0.99875f, z = -0.99875f;
	for (int i = 0; i < _pixels.height(); i++) {
		z = -0.99875f;
		for (int j = 0; j < _pixels.width(); j++) {

			finalColor = ColorDbl(0.0, 0.0, 0.0);

			// Supersampling
			#define SUPERSAMPLING
#ifdef SUPERSAMPLING
			double yDiff, zDiff;
			const int number_of_subsample_rays = 4;
			for (int j = 0; j < number_of_subsample_rays; j++) {

				yDiff = randMinMax(-halfPixelY, halfPixelY);
				zDiff = randMinMax(-halfPixelZ, halfPixelZ);

				Ray thisRay(activeEye, Vertex(x, y + yDiff, z + zDiff, 1.0f));
				if (scene->castRay(thisRay, 0))
				{
					finalColor += thisRay.getColor();
				}
				else
					printf("\nERROR::Camera in function 'render': No ray intersections found.\n");
			}

			finalColor /= number_of_subsample_rays;
#else
			Ray thisRay(activeEye, Vertex(x, y, z, 1.0f));
			if (scene->castRay(thisRay, 0))
			{
				finalColor = thisRay.getColor();
			}
			else
				printf("\nERROR::Camera in function 'render': No ray intersections found.\n");
#endif // SUPERSAMPLING 
			
			thisPixel._color = finalColor;
			_pixels.set(thisPixel, i, j);

			z += pixelSizeZ;
		}

		y += pixelSizeY;
	}
	printf("\nDone!\n");
	createImage();
}

void Camera::createImage() {
	printf("\nWriting image to file...\n");
	double max = findMaxIntensity();
	if (max == 0)
		max = EPSILON;

	std::ofstream output("../Output/RenderImage.ppm");
	output << "P3\n" << _pixels.width() << " " << _pixels.height() << "\n255\n";
	for (int j = _pixels.height() - 1; j >= 0; j--) {
		for (int i = _pixels.width() - 1; i >= 0; i--) {
			
			float r = _pixels.get(i, j)->_color.r * 255.99 / max;
			float g = _pixels.get(i, j)->_color.g * 255.99 / max;
			float b = _pixels.get(i, j)->_color.b * 255.99 / max;

			output << r << " " << g << " " << b << "\n";
		}
	}
	printf("\nDone!\n");
}

double Camera::findMaxIntensity() {
	double max = EPSILON;
	for (int i = 0; i < _pixels.height(); i++) {
		for (int j = 0; j < _pixels.width(); j++) {

			if (_pixels.get(i, j)->_color.r > max)
				max = _pixels.get(i, j)->_color.r;
			if (_pixels.get(i, j)->_color.g > max)
				max = _pixels.get(i, j)->_color.g;
			if (_pixels.get(i, j)->_color.b > max)
				max = _pixels.get(i, j)->_color.b;
		}
	}
	return max;
}