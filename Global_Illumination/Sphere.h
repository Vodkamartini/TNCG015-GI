#ifndef SPHERE_H
#define SPHERE_H
#pragma once
#include "Implicit.h"

class Sphere : public Implicit
{
public:
	Sphere(Vertex center, float radius, ColorDbl color, int material, Vertex position) :
		_center(center), _radius(radius), _radiusSquared(radius * radius), Implicit(color, material, position) {};

	bool rayIntersection(Ray& ray) override;

private:
	const Vertex _center;
	const float _radius;
	const float _radiusSquared;

};
#endif // !SPHERE_H