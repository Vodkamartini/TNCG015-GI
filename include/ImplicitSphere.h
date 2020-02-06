#ifndef IMPLICITSPHERE_H
#define IMPLICITSPHERE_H

#include "Utility.h"
#include "Ray.h"
#include "Material.h"
#include <utility>

class ImplicitSphere {
public:
	ImplicitSphere() 
		: radius(1.0f), radiusSquared(1.0f), center(Vertex(0.0f)), material(Material()) {};

	ImplicitSphere(float radius, Vertex center, Material material) 
		:radius(radius), center(center), material(material)  { radiusSquared = radius * radius; };

	bool rayIntersection(Ray &r);

	bool stableQuadraticSolver(const float& a, const float& b, const float& c, float& x0, float& x1);

	ColorDbl getColor() { return material.getColor(); }
private:
	float radius;
	float radiusSquared;
	Vertex center;
	Material material;
};

#endif // !IMPLICITSPHERE_H
