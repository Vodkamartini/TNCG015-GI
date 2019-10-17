#ifndef CAMERA_H
#define CAMERA_H

#include <vector>
#include <iostream>
#include <fstream>
#include "Utility.h"
#include "Pixel.h"
#include "RayTree.h"

const Vertex EYE_1(4.0f, 0.0f, 0.0f, 0.0f);
const Vertex EYE_2(-1.0f, 0.0f, 0.0f, 0.0f);
const Vertex CAMERA_PLANE[4] = { Vertex(0.0f, -1.0f, -1.0f, 0.0f), Vertex(0.0f, 1.0f, -1.0f, 0.0f), Vertex(0.0f, 1.0f, 0.0f, 1.0f), Vertex(0.0f, -1.0f, 1.0f, 0.0f) };

const bool USING_EYE_1 = true;

const size_t WIDTH = 800;
const size_t HEIGHT = 800;

template <typename T> class Array2D {
public:
	size_t width, height;
	std::vector<T> data;

	Array2D() : width(WIDTH), height(HEIGHT) {};

	Array2D(size_t widthIn, size_t heightIn) : width(widthIn), height(heightIn) {
		data.resize(width * height);
	}

	T* get(size_t x, size_t y) {
		return &(data[getPosition(x, y)]);
	}

	void set(T value, size_t x, size_t y) {
		data[getPosition(x, y)] = value;
	}

private:
	size_t getPosition(size_t x, size_t y) {
		return x + width * y;
	}
};




class Camera {
public:
	Camera() { pixels = Array2D<Pixel>(WIDTH, HEIGHT); };
	void render(Scene* scene);
	void createImage();
	double findMaxIntensity();

private:
	Array2D<Pixel> pixels;
};
#endif // !CAMERA_H
