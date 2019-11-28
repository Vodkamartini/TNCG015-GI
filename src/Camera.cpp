#include "Camera.h"

double Camera::findMaxIntensity() {
	double max = EPSILON;
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (pixels.get(i, j)->getColor().r > max) 
				max = pixels.get(i, j)->getColor().r;
			if (pixels.get(i, j)->getColor().g > max)
				max = pixels.get(i, j)->getColor().g;
			if (pixels.get(i, j)->getColor().b > max)
				max = pixels.get(i, j)->getColor().b;
		}
	}
	return max;
}


void Camera::render(Scene* scene) {

	int count = 0, total = WIDTH * HEIGHT;
	std::cout << "\nCasting rays..." << std::endl;

	ColorDbl finalColor = ColorDbl(0.0, 0.0, 0.0);
	Ray thisRay;
	Pixel thisPixel = Pixel();
	RayTree thisTree = RayTree(scene);

	float pixelSizeY = 2 / (float)(WIDTH);
	float pixelSizeZ = 2 / (float)(HEIGHT);
	//Camera plane params
	float x = 0.0f, y = -0.99875f, z = -0.99875f;
	Vertex active_eye = USING_EYE_1 ? EYE_1 : EYE_2;
	for (int i = 0; i < HEIGHT; i++) {
		z = -0.99875f;
		for (int j = 0; j < WIDTH; j++) {
			
			finalColor = ColorDbl(0.0, 0.0, 0.0);			// 1. Reset color
			thisRay = Ray(active_eye, Vertex(x,y,z,1.0f));	// 2. Cast ray from eye to pixel
			//std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;

			finalColor = thisTree.trace(thisRay);			// 3. Get the color of hit
			thisPixel = Pixel(finalColor);					// 4. Set pixel color
			pixels.set(thisPixel,i,j);						// 5. Add pixel to 2D array

			/*
			// ONLY USE IF DEBUGGING, RUN TIME INCREASES A LOT WITH COUT //
			int progress = 100 * (float)count / total;
			std::cout << "\r" << progress << "%";
			count += 1;
			
			// For debugging: Log color of current pixel
			//std::cout << "r: " << finalColor.r << " g: " << finalColor.g << " " << " b: " << finalColor.b << std::endl;
			*/
	
			z += pixelSizeY;
		}
		y += pixelSizeZ;
	}
	std::cout << "\rDone!" << std::endl;
}

void Camera::createImage() {
	std::cout << "Creating " << WIDTH << "x" << HEIGHT << " ray traced image...";
	double max = findMaxIntensity();
	if (max == 0)
		max = EPSILON;
	std::ofstream output("renderImage.ppm");
	output << "P3\n" << WIDTH << " " << HEIGHT << "\n255\n";
	for (int j = HEIGHT - 1; j >= 0; j--) {
		for (int i = WIDTH - 1; i >= 0; i--) {
			float r = pixels.get(i, j)->getColor().r * (255.99 / max);
			float g = pixels.get(i, j)->getColor().g * (255.99 / max);
			float b = pixels.get(i, j)->getColor().b * (255.99 / max);

			output << r << " " << g << " " << b << "\n";
		
		}
	}
	std::cout << "\nDone!" << std::endl;
}
