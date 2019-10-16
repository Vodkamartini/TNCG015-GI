#include "Pixel.h"

ColorDbl Pixel::getColor() const {
	return color;
}

std::list<Ray> Pixel::getRayList() const {
	return rayList;
}

void Pixel::setColor(ColorDbl& c) {
	color = c;
}

void Pixel::addRay(Ray& r) {
	rayList.push_back(r);
}