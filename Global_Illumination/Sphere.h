#ifndef SPHERE_H
#define SPHERE_H
#pragma once

#include "Object.h"

class Sphere : public Object
{
public:
	Sphere(Vertex center, float radius, ColorDbl color, int material, Vertex position) :
		_center(center), _radius(radius), _radiusSquared(radius * radius), _color(color), Object(material, position) {};

	const ColorDbl getColor() { return _color; };

	bool rayIntersection(Ray& ray) override;
	bool stableQuadraticSolver(const float& a, const float& b, const float& c, float& x0, float& x1);

private:
	const Vertex _center;
	const float _radius;
	const float _radiusSquared;
	const ColorDbl _color;

};
#endif // !SPHERE_H