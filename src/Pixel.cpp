#include "Pixel.h"

void Pixel::addRay(Ray& r) {
	rays.push_back(r);
}

void Pixel::setColor(ColorDb& c) {
	color = c;
}

const ColorDb& Pixel::getColor() const {
	return color;
}

const std::vector<Ray>& Pixel::getRayVector() const {
	return rays;
}

