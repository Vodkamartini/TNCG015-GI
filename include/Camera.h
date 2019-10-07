#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include <array>
#include <iomanip>
#include "Utilities.h"
#include "glm/gtx/string_cast.hpp"
#include "Pixel.h"
#include "Scene.h"

const int WIDTH = 800;	// Width of screen
const int HEIGHT = 800;	// Height of screen

const int MAX_DEPTH = 5;	// Max number of bounces

class Camera {
public:
	void render();
	void createImage();

private:
	//void createPixels();
	double castRays(Scene&);
	ColorDb castRay(Scene&, Ray&, int depth = 0);
	void writeToFile(std::string filename, const double& max);

	Vertex eye1, eye2;	// Eye positions of camera
	std::array<std::array<Pixel, WIDTH>, HEIGHT> pixels;	// Holds all the pixels
	int spp = 50;	// Samples per pixel
	int subPixels = 3; // Number of channels (RGB) of a pixel
};

#endif // !CAMERA_H_INCLUDED