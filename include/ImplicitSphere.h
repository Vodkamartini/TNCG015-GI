#ifndef IMPLICITSPHERE_H
#define IMPLICITSPHERE_H

#include "Utility.h"
#include "Ray.h"
#include <utility>

class ImplicitSphere {
public:
	ImplicitSphere() 
		: radius(1.0f), radiusSquared(1.0f), center(Vertex(0.0f)), color(ColorDbl(0,130,130)) {};

	ImplicitSphere(float radius, Vertex center, ColorDbl color) 
		:radius(radius), center(center), color(color)  { radiusSquared = radius * radius; };

	bool rayIntersection(Ray &r);

	bool stableQuadraticSolver(const float& a, const float& b, const float& c, float& x0, float& x1);
private:
	float radius;
	float radiusSquared;
	Vertex center;
	ColorDbl color;
};

#endif // !IMPLICITSPHERE_H
