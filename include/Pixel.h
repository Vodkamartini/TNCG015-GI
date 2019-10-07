#ifndef PIXEL_H_INCLUDED
#define PIXEL_H_INCLUDED

#include <vector>
#include "Utilities.h"
#include "Scene.h"
#include "Ray.h"

class Pixel {
public:
	Pixel() : color(ColorDb(0.0f)) {};
	Pixel(ColorDb color) : color(color) {};

	void addRay(Ray&);
	void setColor(ColorDb&);

	const ColorDb& getColor() const;
	const std::vector<Ray>& getRayVector() const;

private:
	ColorDb color;			// Color of the pixel
	std::vector<Ray> rays;	// Holds all the rays that goes through the pixel
};

#endif // !PIXEL_H_INCLUDED
