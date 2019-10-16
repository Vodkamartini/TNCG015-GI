#ifndef CAMERA_H
#define CAMERA_H

#include <array>
#include "Utility.h"
#include "Pixel.h"

const Vertex EYE_1(-2.0f, 0.0f, 0.0f, 0.0f);
const Vertex EYE_2(-1.0f, 0.0f, 0.0f, 0.0f);

const bool USING_EYE_1 = true;

const int WIDTH = 800;
const int HEIGHT = 800;

class Camera {
public:
	Camera();
	void render();
	void createImage();
	void createPixels();
private:
	std::array<std::array<Pixel, HEIGHT>, WIDTH> pixels;
};
#endif // !CAMERA_H
