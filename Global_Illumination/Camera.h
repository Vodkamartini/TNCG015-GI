#ifndef CAMERA_H
#define CAMERA_H

#pragma once

#include "utils.h"
#include "Scene.h"
#include "Ray.h"

class Camera
{
public:
	Camera(const Vertex eye1, const Vertex eye2,  size_t width,  size_t height) : _eye1(eye1), _eye2(eye2) {
		_pixels = Array2D<Pixel>(width, height);
	};

	void switchEye();
	void render(Scene* scene);
	

private:
	
	void createImage();
	double findMaxIntensity();

	Vertex _eye1;
	Vertex _eye2;
	bool _using_eye1 = true;

	struct Pixel {
		ColorDbl _color;
		std::vector<Ray> _rays;
	};
	Array2D<Pixel> _pixels;
};



#endif // !CAMERA_H




