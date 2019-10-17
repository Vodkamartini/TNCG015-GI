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
	
	ColorDbl finalColor = ColorDbl(0.0, 0.0, 0.0);
	Ray thisRay;
	Pixel thisPixel = Pixel();
	RayTree thisTree = RayTree(scene);

	float pixelsize = 2 / (float)(HEIGHT * WIDTH);
	float pixelCenter = pixelsize / 2;
	//Camera plane params
	float x = 0, y = 1 - pixelCenter, z = 1 - pixelCenter;
	Vertex active_eye = USING_EYE_1 ? EYE_1 : EYE_2;
	for (int i = 0; i < HEIGHT; i++) {
		y = 1 - pixelCenter;
		for (int j = 0; j < WIDTH; j++) {
		
			finalColor = ColorDbl(0.0, 0.0, 0.0);
			thisRay = Ray(active_eye, Vertex(x,y,z,0));
			finalColor = thisTree.trace(thisRay);
			thisPixel = Pixel(finalColor);
			pixels.set(thisPixel,i,j);

			y -= pixelsize;
		}
		z -= pixelsize;
	}


}

void Camera::createImage() {
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
}
