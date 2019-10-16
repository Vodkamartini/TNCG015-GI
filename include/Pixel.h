#ifndef PIXEL_H
#define PIXEL_H

#include <list>
#include "Utility.h"
#include "Ray.h"

class Pixel {
public:
	Pixel(ColorDbl c = ColorDbl(0));

	void setColor(ColorDbl& color);
	void addRay(Ray& ray);
	ColorDbl getColor() const;
	std::list<Ray> getRayList() const;

private:
	ColorDbl color;
	std::list<Ray> rayList;
};

#endif // !PIXEL_H
